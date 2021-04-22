#include "NumberWithUnits.hpp"
#include "doctest.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace ariel;
using namespace std;

bool t = true;

TEST_CASE("Load & Read from file test")
{
    //open file
    ofstream MyFile("filename.txt");

    // Write to the file
    MyFile << "1 r_km = 1000 r_m\n1 r_m = 100 r_cm\n1 r_kg = 1000 r_g\n1 r_ton = 1000 r_kg\n1 r_hour = 60 r_min\n1 r_min = 60 r_sec\n1 r_USD = 3.33 r_ILS";
    MyFile.close();

    ifstream units_MyFile{"filename.txt"};
    NumberWithUnits::read_units(units_MyFile);
}

//Basic tests
TEST_CASE("Equal function")
{
    NumberWithUnits u5{2, "r_km"};
    NumberWithUnits u6{2, "r_km"};
    NumberWithUnits u9{500, "r_kg"};
    NumberWithUnits u15{30, "r_min"};
    NumberWithUnits u16{30, "r_min"};
    NumberWithUnits u17{0.5, "r_hour"};

    CHECK_EQ(u9, u9);
    CHECK_EQ(u5, u6);
    CHECK_EQ(u16, u15);
    CHECK_EQ(u17, u16); //diff type
    CHECK_EQ(u16, u17);
}

TEST_CASE("Equal function unconnected type")
{
    NumberWithUnits u1{500, "r_cm"};
    NumberWithUnits u5{2, "r_km"};
    NumberWithUnits u12{2, "r_ton"};
    NumberWithUnits u18{60, "r_hour"};
    NumberWithUnits u19{3.33, "r_ILS"}; //1 dolar
    NumberWithUnits u22{6, "r_USD"};

    CHECK_THROWS(u12.operator==(u5));
    CHECK_THROWS(u5.operator==(u12));
    CHECK_THROWS(u22.operator==(u1));
    CHECK_THROWS(u19.operator==(u18));
}

TEST_CASE("not equal function")
{
    NumberWithUnits u1{500, "r_cm"};
    NumberWithUnits u2{1000, "r_cm"}; //10 meter
    NumberWithUnits u3{50, "r_m"};
    NumberWithUnits u4{5000, "r_m"}; //5 km
    NumberWithUnits u7{200, "r_g"};
    NumberWithUnits u8{1000, "r_g"}; //1 kg
    NumberWithUnits u9{500, "r_kg"};
    NumberWithUnits u10{1200, "r_kg"}; //1.2 ton
    NumberWithUnits u11{1.5, "r_ton"};
    NumberWithUnits u12{2, "r_ton"};
    NumberWithUnits u16{30, "r_min"};
    NumberWithUnits u17{0.5, "r_hour"};
    NumberWithUnits u18{60, "r_hour"};
    NumberWithUnits u20{1, "r_ILS"};
    NumberWithUnits u21{2, "r_USD"};

    CHECK_NE(u1, u2); //same type
    CHECK_NE(u2, u1);
    CHECK_NE(u3, u4);
    CHECK_NE(u7, u8);
    CHECK_NE(u9, u10);
    CHECK_NE(u11, u12);
    CHECK_NE(u17, u18);
    CHECK_NE(u21, u20); //diff type
    CHECK_NE(u16, u18);
}

TEST_CASE("not equal function unconnected type")
{
    NumberWithUnits u1{500, "r_cm"};
    NumberWithUnits u4{5000, "r_m"}; //5 km
    NumberWithUnits u5{2, "r_km"};
    NumberWithUnits u11{1.5, "r_ton"};
    NumberWithUnits u12{2, "r_ton"};
    NumberWithUnits u18{60, "r_hour"};
    NumberWithUnits u19{3.33, "r_ILS"}; //1 dolar
    NumberWithUnits u22{6, "r_USD"};

    CHECK_THROWS(t = (u11 != u4));
    CHECK_THROWS(t = (u12 != u5));
    CHECK_THROWS(t = (u22 != u1));
    CHECK_THROWS(t = (u19 != u18));
}

TEST_CASE("Less equal function")
{
    NumberWithUnits u1{500, "r_cm"};
    NumberWithUnits u2{1000, "r_cm"}; //10 meter
    NumberWithUnits u3{50, "r_m"};
    NumberWithUnits u4{5000, "r_m"}; //5 km
    NumberWithUnits u8{1000, "r_g"}; //1 kg
    NumberWithUnits u9{500, "r_kg"};
    NumberWithUnits u10{1200, "r_kg"}; //1.2 ton
    NumberWithUnits u11{1.5, "r_ton"};
    NumberWithUnits u12{2, "r_ton"};
    NumberWithUnits u13{30, "r_sec"};
    NumberWithUnits u14{60, "r_sec"}; //1 min
    NumberWithUnits u16{30, "r_min"};
    NumberWithUnits u17{0.5, "r_hour"};
    NumberWithUnits u18{60, "r_hour"};

    CHECK_LE(u1, u1); //same type
    CHECK_LE(u1, u2);
    CHECK_LE(u3, u4);
    CHECK_LE(u8, u9);
    CHECK_LE(u9, u10);
    CHECK_LE(u11, u12);
    CHECK_LE(u13, u14);
    CHECK_LE(u17, u18);
    CHECK_LE(u16, u17); //diff type
    CHECK_LE(u16, u18);
}

TEST_CASE("Less equal function unconnected type")
{
    NumberWithUnits u1{500, "r_cm"};
    NumberWithUnits u4{5000, "r_m"}; //5 km
    NumberWithUnits u5{2, "r_km"};
    NumberWithUnits u11{1.5, "r_ton"};
    NumberWithUnits u12{2, "r_ton"};
    NumberWithUnits u18{60, "r_hour"};
    NumberWithUnits u19{3.33, "r_ILS"}; //1 dolar
    NumberWithUnits u22{6, "r_USD"};

    CHECK_THROWS(t = (u11 <= u4));
    CHECK_THROWS(t = (u12 <= u5));
    CHECK_THROWS(t = (u22 <= u1));
    CHECK_THROWS(t = (u19 <= u18));
}

TEST_CASE("Less than function")
{
    NumberWithUnits u1{500, "r_cm"};
    NumberWithUnits u2{1000, "r_cm"}; //10 meter
    NumberWithUnits u3{50, "r_m"};
    NumberWithUnits u4{5000, "r_m"}; //5 km
    NumberWithUnits u7{200, "r_g"};
    NumberWithUnits u8{1000, "r_g"}; //1 kg
    NumberWithUnits u9{500, "r_kg"};
    NumberWithUnits u10{1200, "r_kg"}; //1.2 ton
    NumberWithUnits u11{1.5, "r_ton"};
    NumberWithUnits u12{2, "r_ton"};
    NumberWithUnits u13{30, "r_sec"};
    NumberWithUnits u14{60, "r_sec"}; //1 min
    NumberWithUnits u16{30, "r_min"};
    NumberWithUnits u17{0.5, "r_hour"};
    NumberWithUnits u18{60, "r_hour"};

    CHECK_LT(u1, u2); //same type
    CHECK_LT(u3, u4);
    CHECK_LT(u7, u8);
    CHECK_LT(u9, u10);
    CHECK_LT(u11, u12);
    CHECK_LT(u13, u14);
    CHECK_LT(u17, u18);
    CHECK_LE(u16, u18); //diff type
    CHECK_LE(u1, u4);
}

TEST_CASE("Less than function unconnected type")
{
    NumberWithUnits u1{500, "r_cm"};
    NumberWithUnits u4{5000, "r_m"}; //5 km
    NumberWithUnits u5{2, "r_km"};
    NumberWithUnits u11{1.5, "r_ton"};
    NumberWithUnits u12{2, "r_ton"};
    NumberWithUnits u18{60, "r_hour"};
    NumberWithUnits u19{3.33, "r_ILS"}; //1 dolar
    NumberWithUnits u22{6, "r_USD"};

    CHECK_THROWS(t = (u11 < u4));
    CHECK_THROWS(t = (u12 < u5));
    CHECK_THROWS(t = (u22 < u1));
    CHECK_THROWS(t = (u19 < u18));
}

TEST_CASE("greater equal function")
{
    NumberWithUnits u1{500, "r_cm"};
    NumberWithUnits u2{1000, "r_cm"}; //10 meter
    NumberWithUnits u3{50, "r_m"};
    NumberWithUnits u4{5000, "r_m"}; //5 km
    NumberWithUnits u5{2, "r_km"};
    NumberWithUnits u6{2, "r_km"};
    NumberWithUnits u7{200, "r_g"};
    NumberWithUnits u8{1000, "r_g"}; //1 kg
    NumberWithUnits u9{500, "r_kg"};
    NumberWithUnits u10{1200, "r_kg"}; //1.2 ton
    NumberWithUnits u11{1.5, "r_ton"};
    NumberWithUnits u12{2, "r_ton"};
    NumberWithUnits u13{30, "r_sec"};
    NumberWithUnits u14{60, "r_sec"}; //1 min
    NumberWithUnits u16{30, "r_min"};
    NumberWithUnits u17{0.5, "r_hour"};
    NumberWithUnits u18{60, "r_hour"};

    CHECK_GE(u9, u9); //same type
    CHECK_GE(u1, u1);
    CHECK_GE(u2, u1);
    CHECK_GE(u4, u3);
    CHECK_GE(u6, u5);
    CHECK_GE(u8, u7);
    CHECK_GE(u10, u9);
    CHECK_GE(u12, u11);
    CHECK_GE(u14, u13);
    CHECK_GE(u18, u17);
    CHECK_GE(u18, u16); //diff type
    CHECK_GE(u4, u1);
}

TEST_CASE("greater  equal function unconnected type")
{
    NumberWithUnits u1{500, "r_cm"};
    NumberWithUnits u4{5000, "r_m"}; //5 km
    NumberWithUnits u5{2, "r_km"};
    NumberWithUnits u11{1.5, "r_ton"};
    NumberWithUnits u12{2, "r_ton"};
    NumberWithUnits u18{60, "r_hour"};
    NumberWithUnits u19{3.33, "r_ILS"}; //1 dolar
    NumberWithUnits u22{6, "r_USD"};

    CHECK_THROWS(t=(u11>=u4));
    CHECK_THROWS(t=(u12>=u5));
    CHECK_THROWS(t=(u22>=u1));
    CHECK_THROWS(t=(u19>=u18));
}

TEST_CASE("greater than function")
{
    NumberWithUnits u1{500, "r_cm"};
    NumberWithUnits u2{1000, "r_cm"}; //10 meter
    NumberWithUnits u3{50, "r_m"};
    NumberWithUnits u4{5000, "r_m"}; //5 km
    NumberWithUnits u7{200, "r_g"};
    NumberWithUnits u8{1000, "r_g"}; //1 kg
    NumberWithUnits u9{500, "r_kg"};
    NumberWithUnits u10{1200, "r_kg"}; //1.2 ton
    NumberWithUnits u11{1.5, "r_ton"};
    NumberWithUnits u12{2, "r_ton"};
    NumberWithUnits u13{30, "r_sec"};
    NumberWithUnits u14{60, "r_sec"}; //1 min
    NumberWithUnits u16{30, "r_min"};
    NumberWithUnits u17{0.5, "r_hour"};
    NumberWithUnits u18{60, "r_hour"};

    CHECK_GT(u2, u1); //same type
    CHECK_GT(u4, u3);
    CHECK_GT(u8, u7);
    CHECK_GT(u10, u9);
    CHECK_GT(u12, u11);
    CHECK_GT(u14, u13);
    CHECK_GT(u18, u17);
    CHECK_GE(u18, u16); //diff type
    CHECK_GE(u4, u1);
}

TEST_CASE("greater than function unconnected type")
{
    NumberWithUnits u1{500, "r_cm"};
    NumberWithUnits u4{5000, "r_m"}; //5 km
    NumberWithUnits u5{2, "r_km"};
    NumberWithUnits u11{1.5, "r_ton"};
    NumberWithUnits u12{2, "r_ton"};
    NumberWithUnits u18{60, "r_hour"};
    NumberWithUnits u19{3.33, "r_ILS"}; //1 dolar
    NumberWithUnits u22{6, "r_USD"};

    CHECK_THROWS(t=(u11>u4));
    CHECK_THROWS(t=(u12>u5));
    CHECK_THROWS(t=(u22>u1));
    CHECK_THROWS(t=(u19>u18));
}

TEST_CASE("plus function same type")
{
    //create NumberWithUnits
    NumberWithUnits u1{500, "r_cm"};
    NumberWithUnits u2{1000, "r_cm"}; //10 meter
    NumberWithUnits u5{2, "r_km"};
    NumberWithUnits u6{2, "r_km"};
    NumberWithUnits u13{30, "r_sec"};
    NumberWithUnits u14{60, "r_sec"}; //1 min
    NumberWithUnits u15{30, "r_min"};
    NumberWithUnits u16{30, "r_min"};
    NumberWithUnits u17{0.5, "r_hour"};
    NumberWithUnits u18{60, "r_hour"};

    CHECK_EQ(u1 + u1, u2);
    CHECK_EQ(u5 + u6, NumberWithUnits(4, "r_km"));
    CHECK_EQ(u13 + u14, NumberWithUnits(90, "r_sec"));
    CHECK_EQ(u15 + u16, NumberWithUnits(60, "r_min"));
    CHECK_EQ(u17 + u18, NumberWithUnits(60.5, "r_hour"));
}

TEST_CASE("plus function connect type")
{
    //create NumberWithUnits
    NumberWithUnits u1{500, "r_cm"};
    NumberWithUnits u2{1000, "r_cm"}; //10 meter
    NumberWithUnits u15{30, "r_min"};
    NumberWithUnits u16{30, "r_min"};
    NumberWithUnits u19{3.33, "r_ILS"}; //1 dolar
    NumberWithUnits u21{2, "r_USD"};

    CHECK_EQ(u2 + u1 + u1, NumberWithUnits(2000, "r_cm"));
    CHECK_EQ(u15 + u16, NumberWithUnits(1, "r_hour"));
    CHECK_EQ(u19 + u21, NumberWithUnits(3, "r_USD"));
}

TEST_CASE("plus function unconnected type")
{
    NumberWithUnits u4{5000, "r_m"}; //5 km
    NumberWithUnits u11{1.5, "r_ton"};

    CHECK_THROWS(u11 + u4); //diff type
    CHECK_THROWS(u4 + u11);
}

TEST_CASE("plus equal function same type")
{
    NumberWithUnits temp_min_p(30, "r_min");
    temp_min_p += NumberWithUnits(30, "r_min");
    CHECK_EQ(temp_min_p, NumberWithUnits(60, "r_min"));

    NumberWithUnits temp_km_p(3, "r_km");
    temp_km_p += NumberWithUnits(3, "r_km");
    CHECK_EQ(temp_km_p, NumberWithUnits(6, "r_km"));
}

TEST_CASE("plus equal function connect type")
{
    NumberWithUnits temp_min_p(30, "r_min");
    temp_min_p += NumberWithUnits(1, "r_hour");
    CHECK_EQ(temp_min_p, NumberWithUnits(90, "r_min"));

    NumberWithUnits temp_hour_p(1, "r_hour");
    temp_hour_p += NumberWithUnits(30, "r_min");
    CHECK_EQ(temp_hour_p, NumberWithUnits(1.5, "r_hour"));

    NumberWithUnits temp_USD_p(3, "r_USD");
    temp_USD_p += NumberWithUnits(3.33, "r_ILS");
    CHECK_EQ(temp_USD_p, NumberWithUnits(4, "r_USD"));

    NumberWithUnits temp_ILS_p(3.33, "r_ILS");
    temp_ILS_p += NumberWithUnits(1, "r_USD");
    CHECK_EQ(temp_ILS_p, NumberWithUnits(6.66, "r_ILS"));
}

TEST_CASE("plus equal function unconnected type")
{

    NumberWithUnits u4{5000, "r_m"}; //5 km
    NumberWithUnits u11{1.5, "r_ton"};

    CHECK_THROWS(u11 += u4); //unconnected type
    CHECK_THROWS(u4 += u11);
}

TEST_CASE("minus function same type")
{
    //create NumberWithUnits
    NumberWithUnits u1{500, "r_cm"};
    NumberWithUnits u2{1000, "r_cm"}; //10 meter
    NumberWithUnits u5{2, "r_km"};
    NumberWithUnits u6{2, "r_km"};
    NumberWithUnits u13{30, "r_sec"};
    NumberWithUnits u14{60, "r_sec"}; //1 min
    NumberWithUnits u15{30, "r_min"};
    NumberWithUnits u16{30, "r_min"};
    NumberWithUnits u17{0.5, "r_hour"};
    NumberWithUnits u18{60, "r_hour"};

    CHECK_EQ(u1 - u2, NumberWithUnits(-500, "r_cm"));
    CHECK_EQ(u15 - u16, NumberWithUnits(0, "r_min"));
    CHECK_EQ(NumberWithUnits(4, "r_km") - u6, u5);
    CHECK_EQ(NumberWithUnits(60, "r_min") - u15, u16);
    CHECK_EQ(NumberWithUnits(90, "r_sec") - u13, u14);
    CHECK_EQ(NumberWithUnits(60.5, "r_hour") - u17, u18);
}

TEST_CASE("minus function connect type")
{
    //create NumberWithUnits
    NumberWithUnits u1{500, "r_cm"};
    NumberWithUnits u2{1000, "r_cm"}; //10 meter
    NumberWithUnits u15{30, "r_min"};
    NumberWithUnits u16{30, "r_min"};
    NumberWithUnits u19{3.33, "r_ILS"}; //1 dolar
    NumberWithUnits u21{2, "r_USD"};

    CHECK_EQ(u15 - u16, NumberWithUnits(0, "r_hour"));
    CHECK_EQ(u16 - u15, NumberWithUnits(0, "r_hour"));
    CHECK_EQ(u21 - u19, NumberWithUnits(1, "r_USD"));
    CHECK_EQ(u2 - u1 - u1, NumberWithUnits(0, "r_cm"));
    CHECK_EQ(u2 - u1 - u1, NumberWithUnits(0, "r_m"));
    CHECK_EQ(NumberWithUnits(1, "r_hour") - u15, u16);
}

TEST_CASE("minus function unconnected type")
{
    NumberWithUnits u4{5000, "r_m"}; //5 km
    NumberWithUnits u11{1.5, "r_ton"};

    CHECK_THROWS(u11 - u4); //unconnected type
    CHECK_THROWS(u4 - u11);
}

TEST_CASE("minus equal function same type")
{
    NumberWithUnits temp_min_m(30, "r_min");
    temp_min_m -= NumberWithUnits(0, "r_min");
    CHECK_EQ(temp_min_m, NumberWithUnits(30, "r_min"));

    NumberWithUnits temp_km_m(3, "r_km");
    temp_km_m -= NumberWithUnits(2, "r_km");
    CHECK_EQ(temp_km_m, NumberWithUnits(1, "r_km"));
}

TEST_CASE("minus equal function connect type")
{
    NumberWithUnits temp_min_m(30, "r_min");
    temp_min_m -= NumberWithUnits(0.25, "r_hour");
    CHECK_EQ(temp_min_m, NumberWithUnits(15, "r_min"));

    NumberWithUnits temp_hour_m(1, "r_hour");
    temp_hour_m -= NumberWithUnits(30, "r_min");
    CHECK_EQ(temp_hour_m, NumberWithUnits(0.5, "r_hour"));

    NumberWithUnits temp_USD_m(3, "r_USD");
    temp_USD_m -= NumberWithUnits(3.33, "r_ILS");
    CHECK_EQ(temp_USD_m, NumberWithUnits(2, "r_USD"));

    NumberWithUnits temp_ILS_m(6.66, "r_ILS");
    temp_ILS_m -= NumberWithUnits(1, "r_USD");
    CHECK_EQ(temp_ILS_m, NumberWithUnits(3.33, "r_ILS"));
}

TEST_CASE("minus equal function unconnected type")
{
    NumberWithUnits u4{5000, "r_m"}; //5 km
    NumberWithUnits u11{1.5, "r_ton"};

    CHECK_THROWS(u11 -= u4); //unconnected type
    CHECK_THROWS(u4 -= u11);
}

TEST_CASE("++ 'pre' function")
{
    NumberWithUnits pp_pre(1, "r_km");
    ++pp_pre;
    CHECK_EQ(pp_pre, NumberWithUnits(2, "r_km"));
    CHECK_EQ((++pp_pre), NumberWithUnits(3, "r_km"));
    CHECK_EQ((++++++pp_pre), NumberWithUnits(6, "r_km"));
    CHECK_EQ((++--pp_pre), NumberWithUnits(6, "r_km"));
}

TEST_CASE("++ 'post' function")
{
    NumberWithUnits pp_post(1, "r_USD");
    pp_post++;
    CHECK_EQ(pp_post, NumberWithUnits(2, "r_USD"));
    CHECK_EQ((pp_post++), NumberWithUnits(2, "r_USD"));
    CHECK_EQ(pp_post, NumberWithUnits(3, "r_USD"));
}

TEST_CASE("-- 'pre' function")
{
    NumberWithUnits pp_pre(5, "r_ton");
    --pp_pre;
    CHECK_EQ(pp_pre, NumberWithUnits(4, "r_ton"));
    CHECK_EQ((--pp_pre), NumberWithUnits(3, "r_ton"));
    CHECK_EQ((--++pp_pre), NumberWithUnits(3, "r_ton"));
}

TEST_CASE("-- 'post' function")
{
    NumberWithUnits pp_post(9, "r_sec");
    pp_post--;
    CHECK_EQ(pp_post, NumberWithUnits(8, "r_sec"));
    CHECK_EQ((pp_post--), NumberWithUnits(8, "r_sec"));
    CHECK_EQ(pp_post, NumberWithUnits(7, "r_sec"));
}

TEST_CASE("+ 'unary' function")
{
    NumberWithUnits p_u(7, "r_ILS");
    CHECK_EQ((+p_u), NumberWithUnits(7, "r_ILS"));

    NumberWithUnits p_u1(-7, "r_ILS");
    CHECK_EQ((+p_u1), NumberWithUnits(-7, "r_ILS"));
}

TEST_CASE("- 'unary' function")
{
    NumberWithUnits p_u(7, "r_ILS");
    CHECK_EQ((-p_u), NumberWithUnits(-7, "r_ILS"));

    NumberWithUnits p_u1(-7, "r_ILS");
    CHECK_EQ((-p_u1), NumberWithUnits(7, "r_ILS"));
}

TEST_CASE("* 'from left' function")
{
    NumberWithUnits mul(7, "r_ILS");
    CHECK_EQ((2 * mul), NumberWithUnits(14, "r_ILS"));

    NumberWithUnits mul1(-7, "r_g");
    CHECK_EQ((2 * mul1), NumberWithUnits(-14, "r_g"));
    CHECK_EQ((2 * mul1 * 2), NumberWithUnits(-28, "r_g"));
}

TEST_CASE("* 'from right' function")
{
    NumberWithUnits mul3(7, "r_ILS");
    CHECK_EQ((mul3 * 2), NumberWithUnits(14, "r_ILS"));

    NumberWithUnits mul4(-7, "r_g");
    CHECK_EQ((mul4 * 2), NumberWithUnits(-14, "r_g"));
    CHECK_EQ((2 * mul4 * 2), NumberWithUnits(-28, "r_g"));
}

TEST_CASE("<< function")
{
    NumberWithUnits temp_output(7, "r_ILS");
    ostringstream oss;
    oss << temp_output;
    CHECK_EQ(oss.str(), "7[r_ILS]");

    NumberWithUnits temp_output1(-9, "r_km");
    ostringstream oss1;
    oss1 << temp_output1;
    CHECK_EQ(oss1.str(), "-9[r_km]");

    ostringstream oss2;
    oss2 << temp_output << "  " << temp_output1;
    CHECK_EQ(oss2.str(), "7[r_ILS]  -9[r_km]");
}

TEST_CASE(">> function")
{
    NumberWithUnits temp_input(7, "r_ILS");

    istringstream iss("20 [r_sec]");
    iss >> temp_input;
    CHECK_EQ(temp_input, NumberWithUnits(20, "r_sec"));

    istringstream iss1("6[ r_g ]");
    iss1 >> temp_input;
    CHECK_EQ(temp_input, NumberWithUnits(6, "r_g"));

    istringstream iss2(" 900 [r_ton] ");
    iss2 >> temp_input;
    CHECK_EQ(temp_input, NumberWithUnits(900, "r_ton"));

    NumberWithUnits a(7, "r_ILS");
    NumberWithUnits b(7, "r_ILS");
    NumberWithUnits c(7, "r_ILS");
    istringstream iss3{" -16 [r_m]   -7 [r_hour ]  8.8 [r_min ]"};
    iss3 >> a >> b >> c;
    CHECK_EQ(a, NumberWithUnits(-16, "r_m"));
    CHECK_EQ(b, NumberWithUnits(-7, "r_hour"));
    CHECK_EQ(c, NumberWithUnits(8.8, "r_min"));
}

TEST_CASE("insert illigel char")
{
    CHECK_THROWS(NumberWithUnits temp_output(7, "r_IlS"));
    CHECK_THROWS(NumberWithUnits temp_output(7, "r_IlS"));
    CHECK_THROWS(NumberWithUnits temp_output(17, "r_ils"));
    CHECK_THROWS(NumberWithUnits temp_output(27, "r_USd"));
    CHECK_THROWS(NumberWithUnits temp_output(37, "r_Us2"));
    CHECK_THROWS(NumberWithUnits temp_output(47, "r_Km"));
    CHECK_THROWS(NumberWithUnits temp_output(57, "r_KM"));
    CHECK_THROWS(NumberWithUnits temp_output(67, "r_kM"));
    CHECK_THROWS(NumberWithUnits temp_output(77, "r_roei"));
}

TEST_CASE("Mathematical rules order of operations")
{
    CHECK_EQ(2 * NumberWithUnits(-7, "r_hour") + NumberWithUnits(7, "r_hour"), NumberWithUnits(-7, "r_hour"));
    NumberWithUnits temp1(1, "r_USD");
    CHECK_EQ(2 * ++temp1 + NumberWithUnits(3.33, "r_ILS") * 3, NumberWithUnits(7, "r_USD"));
    NumberWithUnits temp2(1, "r_USD");
    CHECK_EQ(2 * temp2++ + NumberWithUnits(3.33, "r_ILS") * 3, NumberWithUnits(5, "r_USD"));
}

TEST_CASE("Load & Read from file2 test")
{
    //open file
    ofstream MyFile2("filename2.txt");

    // Write to the file
    MyFile2 << "1 r_school = 25 r_class\n1 r_class = 25 r_student\n1 r_EUR = 4 r_ILS\n1 r_halfMin = 0.5 r_min";
    MyFile2.close();

    ifstream units_MyFile2{"filename2.txt"};
    NumberWithUnits::read_units(units_MyFile2);
}

//Basic tests
TEST_CASE("Equal function unconnected type after second read")
{
    CHECK_THROWS(t=(NumberWithUnits(2, "r_class")==(NumberWithUnits(2, "r_EUR"))));
    CHECK_THROWS(t=(NumberWithUnits(2, "r_class")!=(NumberWithUnits(2, "r_EUR"))));
    CHECK_THROWS(t=(NumberWithUnits(2, "r_class")<=(NumberWithUnits(2, "r_EUR"))));
    CHECK_THROWS(t=(NumberWithUnits(2, "r_class")<(NumberWithUnits(2, "r_EUR"))));
    CHECK_THROWS(NumberWithUnits(2, "r_class") + (NumberWithUnits(2, "r_EUR")));
    CHECK_THROWS(NumberWithUnits(2, "r_class") += (NumberWithUnits(2, "r_EUR")));
    CHECK_THROWS(NumberWithUnits(2, "r_class") - (NumberWithUnits(2, "r_EUR")));
    CHECK_THROWS(NumberWithUnits(2, "r_class") -= (NumberWithUnits(2, "r_EUR")));
}

TEST_CASE("Equal function after second read")
{
    CHECK_EQ(NumberWithUnits(2, "r_class"), NumberWithUnits(2, "r_class"));
    CHECK_EQ(NumberWithUnits(2, "r_class"), NumberWithUnits(50, "r_student"));
    CHECK_EQ(NumberWithUnits(0.8325, "r_EUR"), NumberWithUnits(1, "r_USD"));
    CHECK_EQ(NumberWithUnits(1, "r_min"), NumberWithUnits(2, "r_halfMin"));
    CHECK_EQ(NumberWithUnits(2, "r_halfMin"), NumberWithUnits(60, "r_sec"));
}

TEST_CASE("not equal function after second read")
{
    CHECK_NE(NumberWithUnits(4, "r_class"), NumberWithUnits(2, "r_class"));
    CHECK_NE(NumberWithUnits(2, "r_class"), NumberWithUnits(25, "r_student"));
    CHECK_NE(NumberWithUnits(1, "r_EUR"), NumberWithUnits(1, "r_ILS"));
    CHECK_NE(NumberWithUnits(2, "r_min"), NumberWithUnits(1, "r_halfMin"));
    CHECK_NE(NumberWithUnits(2, "r_halfMin"), NumberWithUnits(50, "r_sec"));
}

TEST_CASE("Less equal function after second read")
{
    CHECK_LE(NumberWithUnits(1, "r_school"), NumberWithUnits(2, "r_school"));
    CHECK_LE(NumberWithUnits(1, "r_class"), NumberWithUnits(50, "r_student"));
    CHECK_LE(NumberWithUnits(3, "r_EUR"), NumberWithUnits(14, "r_ILS"));
    CHECK_LE(NumberWithUnits(1, "r_hour"), NumberWithUnits(120, "r_halfMin"));
}

TEST_CASE("Less than function after second read")
{
    CHECK_LT(NumberWithUnits(1, "r_school"), NumberWithUnits(750, "r_student"));
    CHECK_LT(NumberWithUnits(1, "r_ILS"), NumberWithUnits(14, "r_EUR"));
    CHECK_LT(NumberWithUnits(1, "r_hour"), NumberWithUnits(121, "r_halfMin"));
    CHECK_LT(NumberWithUnits(25, "r_sec"), NumberWithUnits(1, "r_halfMin"));
}

TEST_CASE("greater equal function after second read")
{
    CHECK_GE(NumberWithUnits(2, "r_school"), NumberWithUnits(1, "r_school"));
    CHECK_GE(NumberWithUnits(50, "r_student"), NumberWithUnits(1, "r_class"));
    CHECK_GE(NumberWithUnits(3, "r_EUR"), NumberWithUnits(10, "r_ILS"));
    CHECK_GE(NumberWithUnits(1, "r_hour"), NumberWithUnits(120, "r_halfMin"));
}

TEST_CASE("greater than function after second read")
{
    CHECK_GT(NumberWithUnits(750, "r_student"), NumberWithUnits(1, "r_school"));
    CHECK_GT(NumberWithUnits(14, "r_EUR"), NumberWithUnits(1, "r_ILS"));
    CHECK_GT(NumberWithUnits(135, "r_halfMin"), NumberWithUnits(1, "r_hour"));
    CHECK_GT(NumberWithUnits(35, "r_sec"), NumberWithUnits(1, "r_halfMin"));
}

TEST_CASE("plus function same type after second read")
{
    CHECK_EQ(NumberWithUnits(25, "r_student") + NumberWithUnits(1, "r_class"), NumberWithUnits(2, "r_class"));
    CHECK_EQ(NumberWithUnits(1, "r_EUR") + NumberWithUnits(1, "r_USD"), NumberWithUnits(7.33, "r_ILS"));
    CHECK_EQ(NumberWithUnits(118, "r_halfMin") + NumberWithUnits(1, "r_min"), NumberWithUnits(1, "r_hour"));
    CHECK_EQ(NumberWithUnits(1, "r_halfMin") + NumberWithUnits(1, "r_halfMin"), NumberWithUnits(2, "r_halfMin"));
}

TEST_CASE("plus equal function same type after second read")
{
    NumberWithUnits temp_min_p(30, "r_min");
    temp_min_p += NumberWithUnits(30, "r_halfMin");
    CHECK_EQ(temp_min_p, NumberWithUnits(45, "r_min"));

    NumberWithUnits temp_USD_p(3, "r_EUR");
    temp_USD_p += NumberWithUnits(3, "r_EUR");
    CHECK_EQ(temp_USD_p, NumberWithUnits(6, "r_EUR"));
}

TEST_CASE("minus function same type after second read")
{
    CHECK_EQ(NumberWithUnits(50, "r_student") - NumberWithUnits(1, "r_class"), NumberWithUnits(1, "r_class"));
    CHECK_EQ(NumberWithUnits(1, "r_EUR") - NumberWithUnits(0.5, "r_EUR"), NumberWithUnits(2, "r_ILS"));
    CHECK_EQ(NumberWithUnits(118, "r_halfMin") - NumberWithUnits(29, "r_min"), NumberWithUnits(0.5, "r_hour"));
    CHECK_EQ(NumberWithUnits(1, "r_halfMin") - NumberWithUnits(1, "r_halfMin"), NumberWithUnits(0, "r_halfMin"));
}

TEST_CASE("minus equal function same type after second read")
{
    NumberWithUnits temp_class_m(30, "r_class");
    temp_class_m -= NumberWithUnits(5, "r_class");
    CHECK_EQ(temp_class_m, NumberWithUnits(1, "r_school"));

    NumberWithUnits temp_min_m(30, "r_min");
    temp_min_m -= NumberWithUnits(30, "r_halfMin");
    CHECK_EQ(temp_min_m, NumberWithUnits(15, "r_min"));
}

TEST_CASE("++/-- 'pre' & 'post' function after second read")
{
    NumberWithUnits pp_pre(1, "r_class");
    ++pp_pre;
    CHECK_EQ(pp_pre, NumberWithUnits(2, "r_class"));

    NumberWithUnits pp_post(1, "r_EUR");
    pp_post++;
    CHECK_EQ(pp_post, NumberWithUnits(2, "r_EUR"));
    CHECK_EQ((pp_post++), NumberWithUnits(2, "r_EUR"));

    NumberWithUnits pp_pre1(5, "r_halfMin");
    --pp_pre1;
    CHECK_EQ(pp_pre1, NumberWithUnits(4, "r_halfMin"));

    NumberWithUnits pp_post1(9, "r_halfMin");
    pp_post1--;
    CHECK_EQ(pp_post1, NumberWithUnits(8, "r_halfMin"));
}

TEST_CASE("+ & - 'unary' function after second read")
{
    NumberWithUnits p_u(7, "r_student");
    CHECK_EQ((+p_u), NumberWithUnits(7, "r_student"));

    NumberWithUnits p_u1(-7, "r_EUR");
    CHECK_EQ((+p_u1), NumberWithUnits(-7, "r_EUR"));

    NumberWithUnits m_u(7, "r_halfMin");
    CHECK_EQ((-m_u), NumberWithUnits(-7, "r_halfMin"));

    NumberWithUnits m_u1(-7, "r_EUR");
    CHECK_EQ((-m_u1), NumberWithUnits(7, "r_EUR"));
}

TEST_CASE("* 'from left' & 'from right' function after second read")
{
    NumberWithUnits mul(7, "r_school");
    CHECK_EQ((2 * mul), NumberWithUnits(14, "r_school"));
    CHECK_EQ((mul * 2), NumberWithUnits(14, "r_school"));
    CHECK_EQ((2 * mul * (-2)), NumberWithUnits(-28, "r_school"));

    NumberWithUnits mul1(7, "r_halfMin");
    CHECK_EQ((2 * mul1), NumberWithUnits(14, "r_halfMin"));
    CHECK_EQ((mul1 * 2), NumberWithUnits(14, "r_halfMin"));
    CHECK_EQ((2 * mul1 * (-2)), NumberWithUnits(-28, "r_halfMin"));
}

TEST_CASE("<< / >> function after second read")
{
    NumberWithUnits temp_output(2, "r_class");
    NumberWithUnits temp_output1(3, "r_student");
    ostringstream oss;
    oss << temp_output << " " << temp_output1;
    CHECK_EQ(oss.str(), "2[r_class] 3[r_student]");

    NumberWithUnits a(7, "r_ILS");
    NumberWithUnits b(7, "r_ILS");
    NumberWithUnits c(7, "r_ILS");
    istringstream iss{" 8 [   r_EUR     ]   -1 [r_school ] 29.7 [r_halfMin ]"};
    iss >> a >> b >> c;
    CHECK_EQ(a, NumberWithUnits(8, "r_EUR"));
    CHECK_EQ(b, NumberWithUnits(-1, "r_school"));
    CHECK_EQ(c, NumberWithUnits(29.7, "r_halfMin"));
}