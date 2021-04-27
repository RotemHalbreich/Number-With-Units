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
        if (!_myMap.contains(unit))
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
            file >> quantity_a >> unit_a >> eq >> quantity_b >> unit_b;

            _myMap[unit_b][unit_a] = 1.0 / quantity_b;
            _myMap[unit_a][unit_b] = quantity_b;

            updateUnits(unit_a, unit_b);
            updateUnits(unit_b, unit_a);

        } while (!file.eof());
    }

    void NumberWithUnits::updateUnits(const string &unit_a, const string &unit_b)
    {
        for (auto &inner : _myMap[unit_a])                       
        {
            double temp = _myMap[unit_b][unit_a] * inner.second;
            _myMap[unit_b][inner.first] = temp;
            _myMap[inner.first][unit_b] = 1.0 / temp;
        }
    }

    double NumberWithUnits::convertUnits(const string &origin, const string &converted, double quantity)
    {
        if (origin == converted)
        {
            return quantity;
        }
        if(!_myMap[origin].contains(converted))
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
        char leftBracket = '[', rightBracket = ']';
        double quantity = 0;
        string unit;

        is >> quantity >> rightBracket;
        do
        {
            if (leftBracket != rightBracket)
            {
                unit.push_back(rightBracket);
            }
            is >> rightBracket;
        } while (rightBracket != ']');

       if(!NumberWithUnits::_myMap.contains(unit))
        {
            throw invalid_argument{"This unit type doesn't exists!"};
        }
        num._quantity = quantity;
        num._unit = unit;
        return is;
    }

    ostream &operator<<(ostream &os, const NumberWithUnits &num)
    {
        return os << num._quantity << "[" << num._unit << "]";
    }
}