#include <string>
#include <list>
#include <utility>

#include <gtest/gtest.h>


#include "lib.hpp"

using namespace aoc;

const std::string example(R"EOS(1=-0-2
12111
2=0=
21
2=01
111
20012
112
1=-1=
1-12
12
1=
122)EOS");

class UnitTest : public ::testing::TestWithParam<std::pair<std::string, int64_t>> {

};

TEST_P(UnitTest, ConvertsFromSnafuToInt) {
    std::string input = GetParam().first;
    int64_t expected = GetParam().second;

    ASSERT_EQ(aoc::snafu_to_int(input), expected);
}

TEST_P(UnitTest, ConvertsFromIntToSnafuString) {
    int64_t input = GetParam().second;
    std::string expected = GetParam().first;

    ASSERT_EQ(aoc::int_to_snafu_string(input), expected);
}

INSTANTIATE_TEST_SUITE_P(day25a, UnitTest, testing::Values(
    std::make_pair("1=-0-2", 1747),
    std::make_pair( "12111",  906),
    std::make_pair(  "2=0=",  198),
    std::make_pair(    "21",   11),
    std::make_pair(  "2=01",  201),
    std::make_pair(   "111",   31),
    std::make_pair( "20012", 1257),
    std::make_pair(   "112",   32),
    std::make_pair( "1=-1=",  353),
    std::make_pair(  "1-12",  107),
    std::make_pair(    "12",    7),
    std::make_pair(    "1=",    3),
    std::make_pair(   "122",   37),
    std::make_pair("1",1),
    std::make_pair("2",2),
    std::make_pair("1=",3),
    std::make_pair("1-",4),
    std::make_pair("10",5),
    std::make_pair("11",6),
    std::make_pair("12",7),
    std::make_pair("2=",8),
    std::make_pair("2-",9),
    std::make_pair("20",10),
    std::make_pair("1=0",15),
    std::make_pair("1-0",20),
    std::make_pair("1=11-2",2022),
    std::make_pair("1-0---0",12345),
    std::make_pair("1121-1110-1=0",314159265),
    std::make_pair("2=-1=0",4890),
    std::make_pair("12--1=10200-22",1651646862),
    std::make_pair("1==-20221",201311),
    std::make_pair("1101-20012",2357507),
    std::make_pair("21-12--21=2-0-0-=0",1656222014965),
    std::make_pair("2-12101=1-",3628204),
    std::make_pair("1==-2",322),
    std::make_pair("12-=0122=1=0-21=",41029931178),
    std::make_pair("120=11=-1=1012-12",211453375857),
    std::make_pair("100=22212-20=-01",30150927851),
    std::make_pair("10-==-0-21111221-=",717523926518),
    std::make_pair("1-=",18),
    std::make_pair("21-2-20-",169924),
    std::make_pair("2-0202-=102-",88698884),
    std::make_pair("1--1-110-=12=",187202283),
    std::make_pair("2-2122=",29558),
    std::make_pair("1=1===2",9692),
    std::make_pair("2--===-10=-111--10",1327596816105),
    std::make_pair("10--1--1101100",1163612650),
    std::make_pair("21-0==-1-=2211",2631964681),
    std::make_pair("2-2202=-0-0=0",463012365),
    std::make_pair("2-2-1-=22=02--0",11432993970),
    std::make_pair("1=2-=10-02120----",102097834219),
    std::make_pair("10==1002=-",1768789),
    std::make_pair("2-0=21-=-0",3491070),
    std::make_pair("1=-=2201112-221==02",2089905037827),
    std::make_pair("10-12-22=2=-",47413539),
    std::make_pair("12-2-00000=-",67109364),
    std::make_pair("1=10=2020200==01-022",12158710750512),
    std::make_pair("1=2=",83),
    std::make_pair("100220",3185),
    std::make_pair("2-1-2",1147),
    std::make_pair("1-12-021--=",8345093),
    std::make_pair("1-022---2=1=010==",124940087613),
    std::make_pair("2201100==21",23530961),
    std::make_pair("11==-002==0==20=0",168215852115),
    std::make_pair("1=22-01-1==2-=1=20",529825261335),
    std::make_pair("221-",304),
    std::make_pair("11=",28),
    std::make_pair("2==2-0021--",14984644),
    std::make_pair("1---212--",295169),
    std::make_pair("202=11--=1-101-01",315221940726),
    std::make_pair("1-----10==12-021=",114461974428),
    std::make_pair("1-02=-00--",1586869),
    std::make_pair("1=0",15),
    std::make_pair("102---",3344),
    std::make_pair("2-2=1==11100",91057025),
    std::make_pair("1=11=2",2017),
    std::make_pair("11200-=102==02=-20",976231063485),
    std::make_pair("11021100-00----0",37167889845),
    std::make_pair("121-0=00=22=10=-",43681520739),
    std::make_pair("2=-=21=",24178),
    std::make_pair("212202=1--1002=",14016856883),
    std::make_pair("10-=2=12--",1848919),
    std::make_pair("2002-2",6297),
    std::make_pair("102-=-",3339),
    std::make_pair("1=0022",1887),
    std::make_pair("2011--0-2==012021",312205672761),
    std::make_pair("12=-0",820),
    std::make_pair("1==--110=2-21",124702111),
    std::make_pair("1-12-11==22-=2001",130425183376),
    std::make_pair("2=1112==22-0020-2",251784125247),
    std::make_pair("2--21=",5553),
    std::make_pair("1==0-0",1620),
    std::make_pair("1=2=-11-=2",1294467),
    std::make_pair("2=120001=20=01-",10107474754),
    std::make_pair("111-1-0=",96348),
    std::make_pair("1-1-00=-2=002",203091627),
    std::make_pair("1==-212=02=1=20-",15735572299),
    std::make_pair("22=",58),
    std::make_pair("1--2",97),
    std::make_pair("10--=11002=1-0-011=",3620852796278),
    std::make_pair("1=01-1=0==0",5923690),
    std::make_pair("1-=0-2---2=12",175527707),
    std::make_pair("1-2-=-",2714),
    std::make_pair("22222",1562),
    std::make_pair("12002=0=021=22022",214009932762),
    std::make_pair("1=-0112021-",5488804),
    std::make_pair("12=-20=0-=2=1",321061666),
    std::make_pair("1=",3),
    std::make_pair("22",12),
    std::make_pair("1==1020--0-1=21=21",403308526336),
    std::make_pair("1=202=0021=2",33328392),
    std::make_pair("1-22-022-1=01",218396326),
    std::make_pair("1==-==1-02=",4963008),
    std::make_pair("1-02-",509),
    std::make_pair("21",11),
    std::make_pair("1=2=010=",51898),
    std::make_pair("2=-==02211",3009681),
    std::make_pair("1-22=--10=1=110-=",136173681993),
    std::make_pair("20-1222=-=1=2-12",60178798982),
    std::make_pair("2012=1-=",160393),
    std::make_pair("111=1=-100=2",59809992),
    std::make_pair("11",6),
    std::make_pair("20-=-20-111202",2371863302),
    std::make_pair("1=01",76),
    std::make_pair("1-12=1-=10-0-1",1041299871),
    std::make_pair("10-02-2",15047),
    std::make_pair("200=01=",31003),
    std::make_pair("1=0002=01222-=100=",458157214498),
    std::make_pair("11-0-=1=011002=-0",176666109570),
    std::make_pair("10-=2-=-",73964),
    std::make_pair("1====2==0=1=02=-=20",1912252192335),
    std::make_pair("11=-020012",2173132),
    std::make_pair("21-11-22-0=0=2",2648230992),
    std::make_pair("1=20011",10631),
    std::make_pair("11-102021=122=-",7132979039),
    std::make_pair("2-2-12021",732136),
    std::make_pair("10--1=21=",372303),
    std::make_pair("100-111",15531),
    std::make_pair("1-2-201=0101-1",1068406896),
    std::make_pair("2=02-00-1=02=2=221=",6158404427178),
    std::make_pair("1-=200=10=0-20",898295610),
    std::make_pair("22=0-==-10=2-1",2829127921),
    std::make_pair("1==",13),
    std::make_pair("11=002=201-2",54713772),
    std::make_pair("2-12",232),
    std::make_pair("211=-12=20=-2=-01-",1695882645504),
    std::make_pair("102-100",16775),
    std::make_pair("10=12210=20=-2",1137573072)
));

TEST(day_25a, example) {
    EXPECT_EQ(aoc::part_a(example), "2=-1=0");
}