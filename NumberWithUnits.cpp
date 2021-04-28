#include <iostream>
#include <fstream>
#include "NumberWithUnits.hpp"

using namespace std;
const double EPS = 0.001;

namespace ariel
{
    unordered_map<string, unordered_map<string, double>> NumberWithUnits::_myMap;

    //Contructor that throws exception
    NumberWithUnits::NumberWithUnits(double quantity, const string &unit)
    {
        if (!_myMap.contains(unit)) // checks if the unit actually exists in the map
        {
            throw invalid_argument{"This unit type doesn't exists!"};
        }
        this->_unit = unit;
        this->_quantity = quantity;
    }

    void NumberWithUnits::read_units(ifstream &file)
    {
        string unit_a, unit_b;
        char eq = '=';
        double quantity_a = 0, quantity_b = 0;
        do
        {
            file >> quantity_a >> unit_a >> eq >> quantity_b >> unit_b; // reads from file, example: file >> 1km = 100000cm

            _myMap[unit_b][unit_a] = 1.0 / quantity_b; // [unit_b]: <cm, <km, 1/100,000>>  note: map[][]-> inner map's value
            _myMap[unit_a][unit_b] = quantity_b;       // [unit_a]: <km, <cm, 100,000>>    note: map[]-> inner map

            updateUnits(unit_a, unit_b);
            updateUnits(unit_b, unit_a);

        } while (!file.eof()); //Run until the end of file
    }

    void NumberWithUnits::updateUnits(const string &unit_a, const string &unit_b)
    {                                      // ~~~EXAMPLE~~~
        for (auto &inner : _myMap[unit_a]) // finds all maps related to [km]: [unit_a]: <km, <cm, 100,000>>
        {
            double temp = _myMap[unit_b][unit_a] * inner.second; // [unit_b]: <cm, <km, 1/100,000 * 100,000>> -> temp = 1
            _myMap[unit_b][inner.first] = temp;                  // <cm, <cm, 1>>
            _myMap[inner.first][unit_b] = 1.0 / temp;            //
        }
    }

    double NumberWithUnits::convertUnits(const string &origin, const string &converted, double quantity)
    {
        if (origin == converted)
        {
            return quantity;
        }
        if (!_myMap[origin].contains(converted)) //if the unit you want to convert to doesn't exists in the map
        {
            throw invalid_argument{"Units do not match - [" + origin + "] cannot be converted to [" + converted + "]"};
        }
        return _myMap[origin][converted] * quantity;
    }

    //Addition and Subtraction operators:
    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &num2)
    {
        double convertedUnit = NumberWithUnits::convertUnits(num2._unit, this->_unit, num2._quantity);
        return NumberWithUnits(this->_quantity + convertedUnit, this->_unit);
    }

    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &num2)
    {
        this->_quantity += NumberWithUnits::convertUnits(num2._unit, this->_unit, num2._quantity);
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator+()
    {
        return NumberWithUnits(this->_quantity, this->_unit);
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &num2)
    {
        double convertedUnit = NumberWithUnits::convertUnits(num2._unit, this->_unit, num2._quantity);
        return NumberWithUnits(this->_quantity - convertedUnit, this->_unit);
    }

    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &num2)
    {
        this->_quantity -= NumberWithUnits::convertUnits(num2._unit, this->_unit, num2._quantity);
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator-()
    {
        return NumberWithUnits(-this->_quantity, this->_unit);
    }

    //Comparison operators:
    bool NumberWithUnits::operator>(const NumberWithUnits &num2) const
    {
        return this->_quantity > NumberWithUnits::convertUnits(num2._unit, this->_unit, num2._quantity);
    }

    bool NumberWithUnits::operator>=(const NumberWithUnits &num2) const
    {
        return *this > num2 || *this == num2;
    }

    bool NumberWithUnits::operator<(const NumberWithUnits &num2) const
    {
        return this->_quantity < NumberWithUnits::convertUnits(num2._unit, this->_unit, num2._quantity);
    }

    bool NumberWithUnits::operator<=(const NumberWithUnits &num2) const
    {
        return *this < num2 || *this == num2;
    }

    bool NumberWithUnits::operator==(const NumberWithUnits &num2) const
    {
        return (abs(this->_quantity - NumberWithUnits::convertUnits(num2._unit, this->_unit, num2._quantity))) <= EPS;
    }

    bool NumberWithUnits::operator!=(NumberWithUnits const &num2) const
    {
        return this->_quantity != NumberWithUnits::convertUnits(num2._unit, this->_unit, num2._quantity);
    }

    //Increment and Decrement operators:
    NumberWithUnits &NumberWithUnits::operator++()
    {
        ++this->_quantity;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator++(int)
    {
        return NumberWithUnits(this->_quantity++, this->_unit);
    }

    NumberWithUnits &NumberWithUnits::operator--()
    {
        --this->_quantity;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator--(int)
    {
        return NumberWithUnits(this->_quantity--, this->_unit);
    }

    //Multiplication operators:
    NumberWithUnits operator*(const double num1, const NumberWithUnits &num2)
    {
        return NumberWithUnits(num1 * num2._quantity, num2._unit);
    }

    NumberWithUnits operator*(const NumberWithUnits &num1, const double num2)
    {
        return NumberWithUnits(num2 * num1._quantity, num1._unit);
    }

    //Input and Output operators:
    istream &operator>>(istream &is, NumberWithUnits &num)
    {
        char ch = 0, leftBracket = '[', rightBracket = ']';
        double quantity = 0;
        string unit;

        is >> quantity >> ch; // starts reading the unit's quantity (1 for instance) and then what's next
        do
        {
            if (ch != leftBracket)  // keep reading chars one by one until you read ']'
            {                       // if char isn't '[', read the unit's chars
                unit.push_back(ch); // if char is '[' append it
            }                       // example: you get -> [km]
            is >> ch;
        } while (ch != rightBracket);
        if (!NumberWithUnits::_myMap.contains(unit)) // checks if the unit actually exists in the map
        {                                            // example: if [km] actually exists
            throw invalid_argument{"This unit type doesn't exists!"};
        }
        num._unit = unit; // if the unit exists, it gets updated by type and quantity
        num._quantity = quantity;
        return is;
    }

    ostream &operator<<(ostream &os, const NumberWithUnits &num)
    {
        return os << num._quantity << "[" << num._unit << "]";
    }
}