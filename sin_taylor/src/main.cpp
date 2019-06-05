
/// @brief Program for calculating SIN(x) by Taylor series


///
#include <fstream>
#include <iostream>
#include <cmath>


///factorial
unsigned long factorial(unsigned n)
{
    if (0 == n) return 1;
    return n * factorial(n - 1);
}

/// function calculating SIN function for given x
double tsin(double x)
{
    ///
    onst unsigned int N = 15;
    double res = 0.0;
    int sign = 1;

    for (unsigned n = 1; n < N; n += 2) {
        double p = std::pow(x, n);
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
