
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

bool HandleCmdLineOptions(int argc, char* argv[], std::vector<std::string>& ifiles, std::string& ofile, EpsilonType& e)
{
    //default values
    e = 0.0;
    ifiles.resize(4);
    ofile = "Y.txt";
    ifiles[0] = "A.txt";
    ifiles[1] = "B.txt";
    ifiles[2] = "C.txt";
    ifiles[3] = "D.txt";
    
    for (IndexType i = 1; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
        std::string s(argv[i]);
        if (s == "-i") {
            for (IndexType j = 0; j < 4; ++j) {
                if (++i < argc && argv[i][0] != '-')  {
                    ifiles[j] = std::string(argv[i]);

                } else  {
                    ErrorReport ("Invalid input files entered" + ifiles[0] + ifiles[1] + ifiles[2] + ifiles[3]);
                    return false;
                }
            }
        } else if (s == "-o") {
            if (++i < argc && argv[i][0] != '-')  {
                ofile = std::string(argv[i]); 
            } else {
                ErrorReport ("Invalid output file");
                return false;
            }
        } else if (s == "-e") {
            if (++i < argc && argv[i][0] != '-')  {
                e = std::stod(std::string(argv[i]));
            } else {
                ErrorReport ("Invalid epsilon value");
                return false;
            }
        } else {
            ErrorReport ("Invalid input data " + s);
            return false;
        }
    }
    return true;
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
            if (std::abs(y.getElement(row, col) - g.getElement(row, col)) > epsilon) {
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
    if (HandleCmdLineOptions(argc, argv, ifiles, ofile, e)) {
        GenerateInputFiles(ifiles);
        MatrixExp(ifiles, ofile);
        Verify(e);
    } else {
        std::cout << "Usage:" << std::endl;
        std::cout << "\tmatrix_exp [-i <ifile1 ifile2 ifile3 ifile4>] [-o <ofile>] [-e <epsilon>]" << std::endl;
    }
    return 0;
}
