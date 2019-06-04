
/// @brief Program for calculating SIN(x) by Taylor 


//
#include <fstream>
#include <iostream>


/// function calculating SIN fiunction for given x
double sin(double x)
{

}

int main ()
{
    std::ifstream input("input.txt");

    double x = 0;
    if (input.is_open()) {
        while (! input.eof()) {
            input >> x;
            std::cout << "sin(" << x << ") = ";
            std::cout << sin(x) << std::endl;
        }
    }

    return 0;
}
