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
        if (_myMap.count(unit) == 0) // checks if the unit actually exists in the map
        {
            throw invalid_argument{"This unit type doesn't exists!"};
        }
        this->_unit = unit;
        this->_quantity = quantity;
    }

    void NumberWithUnits::read_units(ifstream &units_file)
    {
        string unit_a, unit_b;
        char eq = '=';
        double quantity_a = 0, quantity_b = 0;
        do
        {
            units_file >> quantity_a >> unit_a >> eq >> quantity_b >> unit_b; // reads from file, example: units_file >> 1km = 100000cm

            _myMap[unit_b][unit_a] = 1.0 / quantity_b;                        // [unit_b]: <cm, <km, 1/100,000>>  note: map[][]-> inner map's value
            _myMap[unit_a][unit_b] = quantity_b;                              // [unit_a]: <km, <cm, 100,000>>    note: map[]-> inner map

            updateUnits(unit_a, unit_b);
            updateUnits(unit_b, unit_a);

        } while (!units_file.eof()); //Run until the end of file
    }

    void NumberWithUnits::updateUnits(const string &unit_a, const string &unit_b)
    {                                                            // ~~~EXAMPLE~~~
        for (auto &inner : _myMap[unit_a])                       // finds all maps related to [km]: [unit_a]: <km, <cm, 100,000>>
        {
            double temp = _myMap[unit_b][unit_a] * inner.second; // Updates 2 units in both directions:
            _myMap[unit_b][inner.first] = temp;                  // Example: [km]->[m] && [m]->[km]
            _myMap[inner.first][unit_b] = 1.0 / temp;
        }
    }

    double NumberWithUnits::convertUnits(const string &origin, const string &converted, double quantity)
    {
        if (origin == converted)
        {
            return quantity;
        }
        if (_myMap[origin].count(converted) == 0) //if the unit you want to convert to doesn't exists in the map
        {
            throw invalid_argument{"Units do not match - [" + origin + "] cannot be converted to [" + converted + "]"};
        }
        return _myMap[origin][converted] * quantity;
    }

    //Prints the units:
    void NumberWithUnits::printMap()
    {
        cout << "The converted units:" << endl
             << endl;
        for (auto &val : _myMap)
        {
            cout << "Origin unit: [" << val.first << "]" << endl;
            for (auto &inner : _myMap[val.first])
            {
                cout << "              ";
                cout << inner.second << " " << inner.first << endl;
            }
            cout << endl;
        }
    }

    //Addition and Subtraction operators:
    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &num2) const
    {
        double convertedUnit = NumberWithUnits::convertUnits(num2._unit, this->_unit, num2._quantity);
        return NumberWithUnits(this->_quantity + convertedUnit, this->_unit);
    }

    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &num2)
    {
        return *this = *this + num2;
    }

    NumberWithUnits NumberWithUnits::operator+() const
    {
        return NumberWithUnits(this->_quantity, this->_unit);
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &num2) const
    {
        double convertedUnit = NumberWithUnits::convertUnits(num2._unit, this->_unit, num2._quantity);
        return NumberWithUnits(this->_quantity - convertedUnit, this->_unit);
    }

    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &num2)
    {
        return *this = *this - num2;
    }

    NumberWithUnits NumberWithUnits::operator-() const
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
        return !(*this == num2);
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

    NumberWithUnits NumberWithUnits::operator*(const double num2)
    {
        return NumberWithUnits(num2 * this->_quantity, this->_unit);
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

        if (NumberWithUnits::_myMap.count(unit) == 0) // checks if the unit actually exists in the map
        {                                             // example: if [km] actually exists
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