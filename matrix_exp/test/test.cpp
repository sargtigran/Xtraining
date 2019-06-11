
#include "matrix_exp.hpp"

#include <iostream>
#include <string>
#include <cstdlib>

double Rand(double min, double max)
{
    double f = (double)std::rand() / RAND_MAX;
    return min + f * (max - min);
}

void FillMatrix (IndexType N, IndexType M, OutputFile& file, IndexType i) {

    file.writeLine("# Matrix " + std::to_string(i) + "\n");
    file.writeLine(std::to_string(N) + "," + std::to_string(M) + "\n");
    for (IndexType n = 0; n < N; ++n) {
        for (IndexType m = 0; m < M; ++m) {
            if (m != 0) { file.writeLine(","); }
            file.writeNumber(Rand(0.0, 100.0));
        }
        file.writeLine("\n"); 
    }
    file.writeLine("\n"); 
}

void GenerateInputFiles() {
    
    OutputFile a("A.txt"), b("B.txt"), c("C.txt"), d("D.txt");
    const IndexType matrixCnt = 15;
    const IndexType N = 352, M = 235, K = 875;

    for (IndexType i = 0; i < matrixCnt; ++i) {
        FillMatrix(N, M, a, i);
        FillMatrix(N, M, b, i);
        FillMatrix(M, K, c, i);
        FillMatrix(M, K, d, i);
    }
}

void Verify() {}

int main(int argc, char* argv[])
{
    GenerateInputFiles();
    MatrixExp();
    Verify();
    return 0;
}
