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

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <limits>

typedef unsigned int IndexType;
typedef unsigned int ElementType;


struct InputFile { 
    InputFile(const std::string& name) {}
    bool is_open() {
        return false;
    }
};

struct OutputFile {
    OutputFile(const std::string& name) {}
};

struct Matrix {
    
    IndexType getNumRows() const {
        return 0;
    }

    IndexType getNumColumns() const {
        return 0;
    }
    
    ElementType getElement(IndexType i, IndexType j) const {
        return 0;
    }
    
    void setElement (IndexType i, IndexType j, ElementType v) {}
    
    void setSizes(IndexType rows, IndexType cols) {}
};

bool ReadMatrx(const InputFile&, Matrix&) {
    return false;
}

bool WriteMatrix(OutputFile&, const Matrix&) {
    return false;
}

void AddMatrix(const Matrix& a, const Matrix& b, Matrix& c) {
    assert(a.getNumColumns() == b.getNumColumns() &&
           a.getNumRows() == b.getNumRows() && "Invalid matrix sizes");

    c.setSizes(a.getNumRows(), a.getNumColumns());
    for (IndexType i = 0; i < a.getNumColumns(); ++i) {
        for (IndexType j = 0; j < a.getNumRows(); ++j) {
            ElementType aij = a.getElement(i, j);
            ElementType bij = b.getElement(i, j);
            assert(std::numeric_limits<ElementType>::max() - aij >= bij && 
                    std::numeric_limits<ElementType>::min() + bij <= aij);

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

void ErrorReport(const std::string& msg) {
    std::cerr << "ERROR: " << msg << std::endl;
}



int main ()
{
    InputFile A("A.txt"), B("B.txt"), C("C.txt"), D("D.txt");
    OutputFile Y("Y.txt");

    if (A.is_open() && B.is_open() && C.is_open() && D.is_open()) {
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

    return 0;
}
