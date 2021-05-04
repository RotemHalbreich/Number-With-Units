#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <limits>
#include "NumberWithUnits.hpp"

using namespace std;
using namespace ariel;

/**
 *----------------------------------------------------
 * Exercise 3B: Number With Units
 *
 * AUTHORS: Rotem Halbreich
 *
 * To run main program:
 * clang++-9 -std=c++11 main.cpp NumberWithUnits.cpp -o main
 * ./main
 *----------------------------------------------------*/

int main()
{
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    int option;
    string from;
    string to;
    double quantity_from;
    double quantity_to;

    cout << endl
         << "Hey there, Welcome to the Converter!" << endl
         << endl
         << "Insert '1' to present the converted units" << endl
         << "Insert '2' to convert a unit to another unit" << endl
         << "Insert '3' to compare between two units" << endl
         << "Insert '0' to end the program" << endl;

    do
    {
        cout << endl
             << "Please pick an option: ";
        cin >> option;
        cout << endl;

        switch (option)
        {
        case 0:
            cout << "Goodbye, see you soon!" << endl;
            break;

        case 1:
            NumberWithUnits::printMap();
            break;

        case 2:
            cout << "Enter the origin unit type:" << endl;
            cin >> from;
            cout << "Enter the quantity you wish to convert from " << from << ":" << endl;
            cin >> quantity_from;
            cout << "Enter the unit type you wish to convert to:" << endl;
            cin >> to;

            try
            {
                double quantity_converted = NumberWithUnits::convertUnits(from, to, quantity_from);
                cout << quantity_from << '[' << from << ']' << " = " << setprecision(5)
                     << quantity_converted << '[' << to << ']' << endl;
                break;
            }
            catch (...)
            {
                cout << "You've entered a wrong input! these types don't match, please try again!" << endl;
                break;
            }

        case 3:
            cout << "Enter the type of the first unit:" << endl;
            cin >> from;
            cout << "Enter the quantity of " << from << ":" << endl;
            cin >> quantity_from;

            cout << "Enter the type of the second unit:" << endl;
            cin >> to;
            cout << "Enter the quantity of " << to << ":" << endl;
            cin >> quantity_to;

            try
            {
                NumberWithUnits unit_a(quantity_from, from);
                NumberWithUnits unit_b(quantity_to, to);

                if (unit_a == unit_b)
                {
                    cout << unit_a << " = " << unit_b << endl;
                }
                else if (unit_a < unit_b)
                {
                    cout << unit_a << " < " << unit_b << endl;
                }
                else if (unit_a > unit_b)
                {
                    cout << unit_a << " > " << unit_b << endl;
                }
            }
            catch (...)
            {
                cout << "You've entered a wrong input! these types don't match, please try again!"
                     << endl;
                break;
            }
            break;

        default:
            cout << "You've entered a wrong input, please try again!" << endl;
            break;
        }
    } while (option != 0);

    return 0;
}
