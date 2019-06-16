#ifndef MATRIX_EXP_HPP
#define MATRIX_EXP_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <limits>
#include <vector>

/// Type aliases
typedef unsigned int IndexType;
typedef double ElementType;

struct InputFile; 
struct OutputFile;
struct Matrix;

/// Function declarations
void ErrorReport(const std::string& msg);

bool ReadMatrix(InputFile& f, Matrix& a);

bool WriteMatrix(OutputFile& f, const Matrix& a);

void AddMatrix(const Matrix& a, const Matrix& b, Matrix& c);

void MulMatrix(const Matrix& a, const Matrix& b, Matrix& c);

bool VerifyCompatibility(const Matrix& a, const Matrix& b, const Matrix& c, const Matrix& d);

void MatrixExp (const std::vector<std::string>& ifiles, const std::string& ofile);

/// Input file hanling
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
        while (file.good() && ! std::isdigit(file.peek())) {
            if (file.peek() == '#') {
                //ignore comments
                file.ignore(256, '\n');
            } else {
                //ignore separators 
                file.ignore(1);
            }
        }

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

/// Output file hanling
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
            file << num;
            return true;
        }
        return false;
    }

    bool writeLine(const std::string& s) {
        if (file.good()) {
            file << s;
            return true;
        }
        return false;
    }

    std::string getName () const {
        return name;
    }
};


/// Matrix structure handling
struct Matrix {
    
    //Type aliases 
    typedef std::vector<std::vector<ElementType>> MatrixType;

/// data
private:
    IndexType rows;
    IndexType columns;
    MatrixType matrix;

/// public interface
public:
    Matrix() 
        : rows(0)
        , columns(0)
    {}

    void clear() {
        rows = 0;
        columns = 0;
        for (IndexType i = 0; i < rows; ++i) {
            matrix[i].clear();
        }
        matrix.clear();
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
            assert(false);
            exit(4);
        }
        assert(i < matrix.size() && j < matrix[i].size());
        return matrix[i][j];
    }
    
    void setElement (IndexType i, IndexType j, ElementType v) {
        if (i >= rows || j >= columns) {
            ErrorReport("Index out of range");
            assert(false);
            exit(4);
        }
        assert(i < matrix.size());
        assert(j < matrix[i].size());
        matrix[i][j] = v; 
    }
    
    void setSizes(IndexType r, IndexType c) {
        assert(rows == 0 && columns == 0);
        rows = r;
        columns = c;
        matrix.resize(rows);
        for (IndexType i = 0; i < rows; ++i) {
            matrix[i].resize(columns);
        }
    }


    void dump() {
        std::cout << rows << "x" << columns << std::endl;
        for (IndexType i = 0; i < rows; ++i) {
            for (IndexType j = 0; j < columns; ++j) {
                std::cout << matrix[i][j] << " ";
                std::cout.flush();            
            }
            std::cout << std::endl;
        }
    } 
};
#endif // MATRIX_EXP_HPP
