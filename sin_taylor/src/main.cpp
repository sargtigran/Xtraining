
/// @brief Program for calculating SIN(x) by Taylor series


///
#include <fstream>
#include <iostream>
#include <cmath>


/// @brief Returns factorial of n
unsigned long factorial(unsigned n)
{
    if (0 == n) return 1;
    return n * factorial(n - 1);
}

/**
 * @brief returns the value of x in radians
 */
double radians(double x)
{
    const double PI = 3.14159265358979323;
    return x / 180.0 * PI;
}


/**
 * @brief tsin calculating SIN function for given x degree via Taylor series
 * @param x is in degrees
 */
double tsin(double x)
{
    ///
    const unsigned int N = 15;
    double res = 0.0;
    int sign = 1;

    double x_rad = radians(x);
    for (unsigned n = 1; n < N; n += 2) {
        double p = std::pow(x_rad, n);
        unsigned long f = factorial(n);
        res = res + sign * ( p / (double)f );
        sign *= -1;
    }
}

int main ()
{
    std::ifstream input("input.txt");

    double x = 0.0;
    if (input.is_open()) {
        while (! input.eof()) {
            input >> x;
            std::cout << "sin(" << x << ") = ";
            std::cout << tsin(x) << std::endl;
        }
    }

    return 0;
}
