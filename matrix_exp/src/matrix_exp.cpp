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
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <limits>
#include <vector>

typedef unsigned int IndexType;
typedef double ElementType;


void ErrorReport(const std::string& msg) {
    std::cerr << "ERROR: " << msg << std::endl;
}


struct InputFile { 

private:
    std::ifstream file;
    std::string name;

public:
    InputFile(const std::string& n)
        : name(n)
    {
        file.open(n);
    }
    
    bool isOpen() const {
        return file.is_open();
    }

    bool readNumber(ElementType& num) {
        if (file.good()) {
            file >> num;
            return true;
        }
        return false;
    }

    std::string getName () const {
        return name;
    }
};

struct OutputFile {

private:
    std::ofstream file;
    std::string name;

public:
    OutputFile(const std::string& n)
        : name(n)
    {
        file.open(name);
    }
    
    bool isOpen() const {
        return file.is_open();
    }

    bool writeNumber(ElementType num) {
        if (file.good()) {
            file << num << ", ";
            return true;
        }
        return false;
    }

    std::string getName () const {
        return name;
    }
};

struct Matrix {
    
    typedef std::vector<std::vector<ElementType>> MatrixType;

private:
    IndexType rows;
    IndexType columns;
    MatrixType matrix;

public:
    Matrix() 
        : rows(0)
        , columns(0)
    {
    }

    IndexType getNumRows() const {
        return rows;
    }

    IndexType getNumColumns() const {
        return columns;
    }
    
    ElementType getElement(IndexType i, IndexType j) const {
        if (i >= rows || j >= columns) {
            ErrorReport("Index out of range");
            exit(4);
        }
        assert(i < matrix.size() && j < matrix[i].size());
        return matrix[i][j];
    }
    
    void setElement (IndexType i, IndexType j, ElementType v) {
        if (i >= rows || j >= columns) {
            ErrorReport("Index out of range");
            exit(4);
        }
        assert(i < matrix.size() && j < matrix[i].size());
        matrix[i][j] = v; 
    }
    
    void setSizes(IndexType r, IndexType c) {
        assert(rows == 0 && columns == 0);
        rows = r;
        columns = c;
        matrix.resize(rows);
        for (IndexType i = 0; i < columns; ++i) {
            matrix[i].resize(columns);
        }
    }
    
};

bool ReadMatrx(InputFile& f, Matrix& a) {
    
    assert(f.isOpen());
    ElementType n = 0 , m = 0, t = 0;
    if (! f.readNumber(m) || ! f.readNumber(n)) {
        ErrorReport("Could not read form file " + f.getName());
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
            f.writeNumber(a.getElement(i, j));
        }
    }
    return true;
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



int main ()
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

    return 0;
}
