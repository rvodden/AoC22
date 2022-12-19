#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_TARGET_OPENCL_VERSION 210

#include <CL/cl2.hpp>
 
#define MAX_SOURCE_SIZE (0x100000)

const int NUMBER_OF_RESOURCES = 5;

/*
 * Massively parallelize Day 19 in the hope of solving it in reasonable time.
 *
 * Dimension 0 - State
 * Dimeneion 1 - Robot Type
 * Dimension 2 - Resources
 * 
 * A blueprint is a 5x5 array which explains which resources cost which amounts.
 */

using State = std::array<int, NUMBER_OF_RESOURCES*2 + 1>;

class StateHash {
  public:
    std::size_t operator()(const State &state) const {
        std::size_t seed = 9;

        const auto &opp = [](const std::size_t &i, const std::size_t &s){ return i + 0x9e3779b9 + (s << 6) + (s >> 2); };
        for(auto& i : state) seed ^= opp(i, seed);
        
        return seed;
    }
};

std::ostream& operator<< (std::ostream& s, const State &state) {
    if (state[10]) {
        s << "UNVIABLE:" << state[10] << std::endl;
    }

    std::cout << "Resources: ";
    for (int i = 0; i < 5; i++) {
        s << state[i] << ", ";
    }
    std::cout << std::endl;
    
    std::cout << "Robots:    ";
    for (int i = 5; i < 10; i++) {
        s << state[i] << ", ";
    }
    std::cout << std::endl;
    return s;
}

int run() {
    // get all platforms (drivers), e.g. NVIDIA
    std::vector<cl::Platform> all_platforms;
    try {
        cl::Platform::get(&all_platforms);
    } catch (cl::Error &e) {
        std::cerr << "CL Error thrown: (" << e.err() << ") " << e.what() << std::endl;
        if (e.err() == -1001) {
            std::cerr << "Cannot find ICD information. Is OpenCL properly installed?" << std::endl;
        }
        throw e;
    }
    
    cl::Platform default_platform=all_platforms[0];
    std::cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";

    // get default device (CPUs, GPUs) of the default platform
    std::vector<cl::Device> all_devices;
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if(all_devices.empty()){
        std::cout<<" No devices found. Check OpenCL installation!\n";
        exit(1);
    }

    cl::Device device=all_devices[0];
    std::cout<< "Using device: "<<device.getInfo<CL_DEVICE_NAME>()<<"\n";

    // a context is like a "runtime link" to the device and platform;
    // i.e. communication is possible
    cl::Context context({device});

    std::fstream filestream("day19.cl");
    const std::string source(std::istreambuf_iterator<char>(filestream), (std::istreambuf_iterator<char>()));

    cl::Program::Sources sources;
    sources.push_back(source);

    cl::Program program(context, sources);
    try {
        program.build();
    } catch (cl::Error &e) {
        std::cout << e.what() << " : " << e.err() << std::endl;

        if (e.err() == CL_BUILD_PROGRAM_FAILURE) {
            // Check the build status
            cl_build_status status = program.getBuildInfo<CL_PROGRAM_BUILD_STATUS>(device);
            if (status == CL_BUILD_ERROR) {
                // Get the build log
                std::string name     = device.getInfo<CL_DEVICE_NAME>();
                std::string buildlog = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device);
                std::cerr << "Build log for " << name << ":" << std::endl
                            << buildlog << std::endl;
            }
        }
        throw e;
    }

    // first dimension is the type of robot, the second is the resource cost
    // i.e. [0][1] is the clay cost of a ore robot  
    using A = std::array<int, NUMBER_OF_RESOURCES>;
    std::vector<std::array<A,NUMBER_OF_RESOURCES>> blueprints_h = {{
        A{ 4,  0, 0, 0, 0 },
        A{ 2,  0, 0, 0, 0 }, 
        A{ 3, 14, 0, 0, 0 },
        A{ 2,  0, 7, 0, 0 },
        A{ 0,  0, 0, 0, 0 }
    }};

    // make this one bigger than the number of resources so that we can store the max from the previous round.
    std::vector<std::array<int, NUMBER_OF_RESOURCES + 2>> limits_h;
    for (const auto &blueprint : blueprints_h) {

        std::array<int,NUMBER_OF_RESOURCES + 2> max = {0, 0, 0, 0, 0, 0, 0};
        for( int i = 0; i < NUMBER_OF_RESOURCES; i++ ) {
            for ( const auto &type : blueprint ) {
                max[i] = std::max(type[i], max[i]);
            }
        }
        limits_h.push_back(max);
    }

    // resources first; robots second; then a "valid" bit to flag if this is a dead end or not
    std::vector<State> input_states_h = {
        State {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}
    };
    
    std::vector<State> output_states_h(5);

    cl::CommandQueue queue(context, device);
    
    cl::Buffer blueprint_d(context, blueprints_h[0].begin(), blueprints_h[0].end(), true);
    cl::Buffer input_states_d(context, input_states_h.begin(), input_states_h.end(), true);
    cl::Buffer limits_d(context, limits_h[0].begin(), limits_h[0].end(), true);
    cl::Buffer output_states_d(context, CL_MEM_READ_WRITE | CL_MEM_HOST_READ_ONLY, sizeof(int) * input_states_h.size() * input_states_h.front().size() * 5);
    

    cl::copy(queue, blueprints_h[0].begin(), blueprints_h[0].end(), blueprint_d);

    const int steps = 24;
    
    for(int i = 0; i < steps; i++) { 
        // std::cout << std::endl << "*********************************************" << std::endl;
        limits_h[0][NUMBER_OF_RESOURCES + 1] = steps - i;
        try{
            cl::copy(queue, input_states_h.begin(), input_states_h.end(), input_states_d);
            cl::copy(queue, limits_h[0].begin(), limits_h[0].end(), limits_d);
            cl::Kernel day19(program, "day19");
            day19.setArg(0, blueprint_d);
            day19.setArg(1, limits_d);
            day19.setArg(2, input_states_d);
            day19.setArg(3, output_states_d);
            // first round there is only one state
            queue.enqueueNDRangeKernel(day19, cl::NullRange, cl::NDRange(input_states_h.size(),NUMBER_OF_RESOURCES), cl::NullRange);
            queue.finish();
            cl::copy(queue, output_states_d, output_states_h.begin(), output_states_h.end());
        } catch (cl::Error &e) {
            std::cout << e.what() << " : " << e.err() << std::endl;
            throw e;
        }

        // for (const auto &s : output_states_h)
        //     std::cout << s << std::endl;
        
        input_states_h.clear();
        limits_h[0][NUMBER_OF_RESOURCES] = 0;
        for( const auto& istate : output_states_h ) {
            if (istate[10] != 0) continue;
            input_states_h.push_back(istate);
            limits_h[0][NUMBER_OF_RESOURCES] = std::max(limits_h[0][NUMBER_OF_RESOURCES], istate[3]);
        }

        std::cout << std::endl << "Next Frontier is " << input_states_h.size() << " option(s). Max so far is " << limits_h[0][NUMBER_OF_RESOURCES] << std::endl;
        
        // for (const auto &s : input_states_h)
        //     std::cout << s << std::endl;

        input_states_d = cl::Buffer(context, input_states_h.begin(), input_states_h.end(), true);
        output_states_h = std::vector<State>(input_states_h.size() * NUMBER_OF_RESOURCES);
        output_states_d = cl::Buffer(context, CL_MEM_READ_WRITE | CL_MEM_HOST_READ_ONLY, sizeof(int) * input_states_h.size() * input_states_h.front().size() * NUMBER_OF_RESOURCES);
    }

    return 0;
}