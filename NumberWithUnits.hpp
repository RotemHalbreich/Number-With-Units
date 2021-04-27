#pragma once
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>

namespace ariel
{
    class NumberWithUnits
    {
    private:
        double _quantity;
        std::string _unit;
        static std::unordered_map<std::string, std::unordered_map<std::string, double>> _myMap;

        //private functions:
        static double convertUnits(const std::string &src, const std::string &dest, double quantity);
        static void updateUnits(const std::string &unit_a, const std::string &unit_b);

    public:
        //Constructor:
        NumberWithUnits(double quantity, const std::string &unit);

        //Public functions:
        static void read_units(std::ifstream &file);

        //Addition and Subtraction operators:
        NumberWithUnits operator+(const NumberWithUnits &num2);   //addition
        NumberWithUnits &operator+=(const NumberWithUnits &num2); //addition assignment
        NumberWithUnits operator+();                              //unary plus
        NumberWithUnits operator-(const NumberWithUnits &num2);   //subtraction
        NumberWithUnits &operator-=(const NumberWithUnits &num2); //subtraction assignment
        NumberWithUnits operator-();                              //unary negation

        //Comparison operators:
        bool operator>(const NumberWithUnits &num2) const;  //greater than
        bool operator>=(const NumberWithUnits &num2) const; //greater than or equal
        bool operator<(const NumberWithUnits &num2) const;  //less than
        bool operator<=(const NumberWithUnits &num2) const; //less than or equal
        bool operator==(const NumberWithUnits &num2) const; //equal
        bool operator!=(const NumberWithUnits &num2) const; //not equal

        //Increment and Decrement operators:
        NumberWithUnits &operator++();   //prefix increment
        NumberWithUnits operator++(int); //postfix increment
        NumberWithUnits &operator--();   //prefix decrement
        NumberWithUnits operator--(int); //postfix decrement

        //Multiplication operators:
        friend NumberWithUnits operator*(const double num1, const NumberWithUnits &num2); //multiplication
        friend NumberWithUnits operator*(const NumberWithUnits &num1, const double num2); //multiplication

        //Input and Output operators:
        friend std::istream &operator>>(std::istream &is, NumberWithUnits &num);       //input
        friend std::ostream &operator<<(std::ostream &os, const NumberWithUnits &num); //outpput
    };
}