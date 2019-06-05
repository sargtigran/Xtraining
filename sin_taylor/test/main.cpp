
/// @brief Program for calculating SIN(x) by Taylor series

/// Internal headers
#include "tsin.hpp"

/// Standard headers
#include <fstream>
#include <iostream>


int main ()
{
    std::ifstream input("test/input.txt");
    std::ofstream output("test/output.txt");

    double x = 0.0;
    if (input.is_open()) {
        while (! input.eof()) {
            input >> x;
            std::cout << "sin(" << x << ") = ";
            std::cout << tsin(x) << std::endl;
            output << tsin(x) << std::endl;
        }
    }

    return 0;
}
