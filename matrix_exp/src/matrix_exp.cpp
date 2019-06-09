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

struct InputFile { 
    InputFile(const std::string& name) {}
    bool is_open() {
        return false;
    }
};

struct OutputFile {
    OutputFile(const std::string& name) {}
};

struct Matrix { };

bool ReadMatrx(const InputFile&, Matrix&) {
    return false;
}

bool WriteMatrix(OutputFile&, const Matrix&) {
    return false;
}

void AddMatrix(const Matrix&, const Matrix&, Matrix&) {};

void MulMatrix(const Matrix&, const Matrix&, Matrix&) {};

bool VerifyCompatibility(const Matrix&, const Matrix&, const Matrix&, const Matrix&) {
    return false;
}

void ErrorReport(const std::string& msg) {}


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
