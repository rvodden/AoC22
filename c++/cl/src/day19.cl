__constant const int NUMBER_OF_RESOURCE_TYPES = 5;
__constant const int SIZE_OF_STATE = NUMBER_OF_RESOURCE_TYPES*2 + 1;
__constant const int BIGINT = 65000;
__constant const int NUMBER_OF_CYCLES = 26; // can we upload this?

__kernel void day19(
    global const int* blueprint, 
    global const int* limits,
    global const int* input_states,
    global int* output_states
) {
    int state_number     = get_global_id(0);
    int robot_type       = get_global_id(1);

    int output_state_location;

    int resource_cost;
    int resource_available;
    int robot_count;


    int base_blueprint = NUMBER_OF_RESOURCE_TYPES * robot_type;
    int base_input_state = state_number * SIZE_OF_STATE;
    int base_output_state = (state_number * SIZE_OF_STATE * NUMBER_OF_RESOURCE_TYPES) + robot_type * SIZE_OF_STATE;    

    int max_so_far = limits[NUMBER_OF_RESOURCE_TYPES];
    int remaining_cyles = limits[NUMBER_OF_RESOURCE_TYPES + 1];
    
    // check if we can buy a robot
    for (int resource_number = 0; resource_number < NUMBER_OF_RESOURCE_TYPES; resource_number++ ) {
        // printf("State: %d; Robot Type: %d; Resource Type: %d\n", state_number, robot_type, resource_number);
        resource_cost = blueprint[base_blueprint + resource_number];
        resource_available = input_states[base_input_state + resource_number];
        robot_count = input_states[base_input_state + NUMBER_OF_RESOURCE_TYPES + resource_number];

        if (resource_cost > resource_available) { // don't buy a robot if we can't afford it
            output_states[base_output_state + 10] = 1; // NOT VIABLE
            return;
        }

        if(limits[resource_number] != 0 && robot_count >= limits[resource_number]) { // we can only build 1 robot in a turn, so if we're already 
                                                                                     // collected enough for all robots in 1 turn stop.
            output_states[base_output_state + 10] = 1; // NOT VIABLE
            return;
        }
        
        if(input_states[base_input_state + 3] + 2 < max_so_far) {
            output_states[base_output_state + 10] = 1; // NOT VIABLE
            return;
        }
    }
    

    // buy the robot if we can
    for (int resource_number = 0; resource_number < NUMBER_OF_RESOURCE_TYPES; resource_number++ ) {
        resource_cost = blueprint[base_blueprint + resource_number];
        resource_available = input_states[base_input_state + resource_number];
        robot_count = input_states[base_input_state + NUMBER_OF_RESOURCE_TYPES + resource_number];
        
        output_state_location = base_output_state + resource_number;
        output_states[output_state_location] = resource_available - resource_cost + robot_count;
        if(resource_number == robot_type)
            output_states[output_state_location + NUMBER_OF_RESOURCE_TYPES] = robot_count + 1;
        else
            output_states[output_state_location + NUMBER_OF_RESOURCE_TYPES] = robot_count;
    }
    output_state_location++;
    output_states[base_output_state + 10] = 0; // VIABLE
};