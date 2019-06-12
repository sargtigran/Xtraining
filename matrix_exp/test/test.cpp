
#include "matrix_exp.hpp"

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>


typedef double EpsilonType;

ElementType Rand(ElementType min, ElementType max)
{
    ElementType f = (ElementType)std::rand() / RAND_MAX;
    return min + f * (max - min);
}

void HandleCmdLineOptions(int argc, char* argv[], std::vector<std::string>& ifiles, std::string& ofile, EpsilonType& e)
{

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

void GenerateInputFiles(const std::vector<std::string>& ifiles) {
    
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

bool IsMatrixEqual(const Matrix& y, const Matrix& g, IndexType& row, IndexType& col, EpsilonType epsilon) {

    if (y.getNumRows() != g.getNumRows() || y.getNumColumns() != g.getNumColumns()) {
        return false;
    }

    for (row = 0; row < g.getNumRows(); ++row) {
        for (col = 0; col < g.getNumColumns(); ++col) {
            if (std::abs(y.getElement(row, col) - g.getElement(row, col)) >= epsilon) {
                return false;
            }
        }
    }
    return true;
}

void Verify(EpsilonType epsilon) {
    InputFile Y("Y.txt"), G("Y.gold");
    if (!Y.isOpen() || ! G.isOpen()) {
        ErrorReport("FAILED (Input files are not opened correctly)");
        exit(1);
    }
    
    Matrix y, g;
    IndexType row = 0, col = 0;
    for(IndexType i = 0; (ReadMatrix(Y, y) && ReadMatrix(G, g)); ++i) {
        std::cout << "Comparing matrix: " << i << " ........... ";
        if (IsMatrixEqual(y, g, row, col, epsilon)) {
            std::cout << "PASS" << std::endl;
        } else {
            std::cout << "FAIL" << std::endl;
            std::cout << "\t Faild in position [" << row << "][" << col << "] of matrix: " << i << std::endl; 
        }
    }   
}

int main(int argc, char* argv[])
{
    std::vector<std::string> ifiles;
    std::string ofile;
    EpsilonType e;
    HandleCmdLineOptions(argc, argv, std::vector<std::string>& ifiles, std::string& ofile, EpsilonType& e);
    GenerateInputFiles(ifiles);
    MatrixExp(ifiles, ofile);
    Verify(e);
    return 0;
}
