
#include "matrix_exp.hpp"

#include <iostream>
#include <string>

void FillMatrix (IndexType N, IndexType M, OutputFile& file, IndexType i) {

    file.writeLine("#Matrix " + std::to_string(i) + "\n");
    file.writeLine(std::to_string(N) + "," + std::to_string(M) + "\n");
    for (IndexType n = 0; n < N; ++n) {
        for (IndexType m = 0; m < M; ++m) {
            if (m != 0) { file.writeLine(","); }
            file.writeNumber(1);
        }
        file.writeLine("\n"); 
    }
    file.writeLine("\n"); 
}

void GenerateInputFiles() {
    
    OutputFile a("A.txt"), b("B.txt"), c("C.txt"), d("D.txt");
    const IndexType matrixCnt = 2;
    const IndexType N = 10, M = 5, K = 15;

    for (IndexType i = 0; i < matrixCnt; ++i) {
        FillMatrix(N, M, a, i);
        FillMatrix(N, M, b, i);
        FillMatrix(M, K, c, i);
        FillMatrix(M, K, d, i);
    }
}

int main(int argc, char* argv[])
{

    GenerateInputFiles();
    MatrixExp();
    return 0;
}
