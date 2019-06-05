
/// @brief Program for calculating SIN(x) by Taylor series


///
#include <fstream>
#include <iostream>
#include <cmath>


///factorial
long factorial(int n)
{

}

/// function calculating SIN function for given x
double tsin(double x)
{
    ///
    const double pi = 3.14159265358979323846;
    const int N = 10;
    double res = 0.0;
    for (int n = 1; n < N; n += 2) {
        double p = std::pow(x, n);
        long f = factorial(n);
        res += p / f;
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
