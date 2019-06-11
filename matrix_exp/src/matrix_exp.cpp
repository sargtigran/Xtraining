/**
 * @brief Program calculating matrix expression 
 * Y = (A + B)*(C + D)
 * where A,B,C,D,Y are matrices 
 *
 * Input:
 *  A.txt, B.txt, C.txt, D.txt
 *  files with content:
 *  
 *  M, N
 *  a1[0,0] ... a1[0,N]
 *  .
 *  .
 *  a1[M,0] ... a1[M,N]
 *  ...
 *
 * Output:
 *  Y.txt
 *  file with content:
 *
 * y1[0,0] ... y1[0,N]
 * .
 * .
 * .
 * y1[M,0] ... y1[M,N]
 *
 */

//Project headers
#include "matrix_exp.hpp"

//Standard headers
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <limits>
#include <vector>

void ErrorReport(const std::string& msg) {
    std::cerr << "ERROR: " << msg << std::endl;
}

bool ReadMatrx(InputFile& f, Matrix& a) {
    
    assert(f.isOpen());
    ElementType n = 0 , m = 0, t = 0;
    if (! f.readNumber(m) || ! f.readNumber(n)) {
        return false;
    }
    
    a.setSizes(m, n);
    for (IndexType i = 0; i < m; ++i) {
        for (IndexType j = 0; j < n; ++j) {
            if (f.readNumber(t)) {
                a.setElement(i, j, t);
            } else {
                ErrorReport("Could not read form file " + f.getName());
                return false;
            }
        }
    }

    return true;
}

bool WriteMatrix(OutputFile& f, const Matrix& a) {
    if (! f.isOpen()) {
        ErrorReport("Could not write to file " + f.getName());
        return false;
    }
    for (IndexType i = 0; i < a.getNumRows(); ++i) {
        for (IndexType j = 0; j < a.getNumColumns(); ++j) {
            if (j != 0) { f.writeLine(","); } 
            f.writeNumber(a.getElement(i, j));
        }
        f.writeLine("\n");
    }
    return true;
}

void AddMatrix(const Matrix& a, const Matrix& b, Matrix& c) {
    assert(a.getNumColumns() == b.getNumColumns() &&
           a.getNumRows() == b.getNumRows() && "Invalid matrix sizes");

    c.setSizes(a.getNumRows(), a.getNumColumns());
    for (IndexType i = 0; i < a.getNumRows(); ++i) {
        for (IndexType j = 0; j < a.getNumColumns(); ++j) {
            ElementType aij = a.getElement(i, j);
            ElementType bij = b.getElement(i, j);
            assert(std::numeric_limits<ElementType>::max() - aij >= bij); 
            //assert(std::numeric_limits<ElementType>::min() + bij <= aij);

            c.setElement(i, j, aij + bij);
        }
    }
};

void MulMatrix(const Matrix& a, const Matrix& b, Matrix& c) {
    assert(a.getNumColumns() == b.getNumRows() && "Invalid matrix sizes");

    c.setSizes(a.getNumRows(), b.getNumColumns());
    for (IndexType i = 0; i < a.getNumRows(); ++i) {
        for (IndexType j = 0; j < b.getNumColumns(); ++j) {
            ElementType s = 0;
            for (IndexType k = 0; k < a.getNumColumns(); ++k) {
                //TODO: set assertion for overflow
                s += a.getElement(i, k) * b.getElement(k, j);
            }
            c.setElement(i, j, s);
        }
    }
};

bool VerifyCompatibility(const Matrix& a, const Matrix& b, const Matrix& c, const Matrix& d) {
    return a.getNumRows() == b.getNumRows() && a.getNumColumns() == b.getNumColumns()
             && c.getNumRows() == d.getNumRows() && c.getNumColumns() == d.getNumColumns()
             && a.getNumColumns() == c.getNumRows();
}

void MatrixExp ()
{
    InputFile A("A.txt"), B("B.txt"), C("C.txt"), D("D.txt");
    OutputFile Y("Y.txt");

    if (A.isOpen() && B.isOpen() && C.isOpen() && D.isOpen()) {
        Matrix a, b, c, d;
        while (ReadMatrx(A, a) && ReadMatrx(B, b) && ReadMatrx(C, c) && ReadMatrx(D, d)) {
            if (! VerifyCompatibility(a, b, c, d)) {
                ErrorReport("Incompatible matrices are read");
                exit(1); 
            }
            Matrix tmp1, tmp2, y;
            AddMatrix(a, b, tmp1);
            AddMatrix(c, d, tmp2);
            MulMatrix(tmp1, tmp2, y);
            WriteMatrix(Y, y);
        }
    } else {
        ErrorReport("Files are incorrect");
        exit(2);
    }
}
