
#ifndef JAKOBI_HPP
#define JAKOBI_HPP

#include <vector>

using ElementType = double;
using Matrix = std::vector<std::vector<ElementType>>;
using Vector = std::vector<ElementType>;


bool CheckAcurracy(const Vector& x1, const Vector& x2, const double eps);
void SolveJakobiMethod(const Matrix& A, const Vector& b, Vector& x);
void SolveGaussZeidelMethod(const Matrix& A, const Vector& b, Vector& x);

#endif //JAKOBI_HPP
