// Parth Kalkar, BS-19, Joint Assignment 3

#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

class Matrix {
protected:
    int n, m;

    double** mt;
public:
    Matrix() {
        n = 0;
        m = 0;
        mt = nullptr;
    }

    Matrix(int n, int m) {
        this->n = n;
        this->m = m;

        mt = new double* [n];
        for (int i = 0; i < n; i++) {
            mt[i] = new double[m];
        }
    }

    Matrix(const Matrix& matrix) : Matrix() {
        if (matrix.mt != nullptr) {
            n = matrix.n;
            m = matrix.m;
            mt = new double* [n];
            for (int i = 0; i < n; ++i)
                mt[i] = new double[m];
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j)
                    mt[i][j] = matrix.mt[i][j];
        }
    }


    int getN() {
        return n;
    }

    int getM() {
        return m;
    }

    double** getMatrix() {
        return mt;
    }


    friend istream& operator>>(istream& in, Matrix& matrix) {
        for (int i = 0; i < matrix.n; i++) {
            for (int j = 0; j < matrix.m; j++) {
                in >> matrix.mt[i][j];
            }
        }
        return in;
    }


    friend ostream& operator<<(ostream& out, const Matrix& matrix) {
        for (int i = 0; i < matrix.n; i++) {
            for (int j = 0; j < matrix.m; j++) {
                out << fixed << setprecision(4) << round(matrix.mt[i][j] * 10000) / 10000;
                if (j != matrix.m - 1) {
                    out << ' ';
                }
            }
            if (i != matrix.n - 1) {
                out << endl;
            }
        }
        out << endl;
        return out;
    }

    Matrix operator*(Matrix& M) {
        Matrix N(n,M.m);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < M.m; j++) {
                N.mt[i][j] = 0;
                for (int k = 0; k < m; k++) {
                    N.mt[i][j] = N.mt[i][j] + mt[i][k] * M.mt[k][j];
                }
            }
        }
        return N;
    }
     Matrix operator+(Matrix M) {

        Matrix N(n, m);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
            {
                N.mt[i][j] = mt[i][j] + M.mat[i][j];
            }
        }

        return N;
    }
    Matrix& operator=(const Matrix& M) {
        n = M.n;
        m = M.m;
        mt = new double* [n];
        for (int i = 0; i < n; ++i)
            mt[i] = new double[m];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                mt[i][j] = M.mt[i][j];
        return *this;
    }





    Matrix operator-(Matrix M) {
        Matrix N(n, m);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
            {
                N.mt[i][j] = mt[i][j] - M.mat[i][j];
            }
        }
        return N;
    }





    bool isEmpty() {
        if (mt == nullptr) {
            return true;
        }
        else {
            return false;
        }
    }

    bool CheckApplicable() {
        for (int i = 0; i < n; i++) {
            double sum = 0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    sum += mt[i][j];
                }
            }
            if (abs(sum) > abs(mt[i][i])) {
                return false;
            }
        }
        return true;
    }
    void divide(Matrix* beta) {
        for (int i = 0; i < n; i++) {
            double d = mt[i][i];
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    mt[i][j] = 0;
                }
                else {

                    mt[i][j] = mt[i][j] / d * (-1);
                }
            }
            (*beta).getMatrix()[i][0] /= d;
        }
    }


    void JacobiMethod(Matrix* beta, double e) {
        int step = -1;
        Matrix x(n, 1);
        Matrix x_previous(n, 1);
        for (int i = 0; i < n; i++) {
            x.mt[i][0] = 0;
            x_previous.mt[i][0] = 0;
        }
        double eps;
        do {
            eps = 0;
            if (step == -1) {
                x = (*beta);
                x_previous = x;
                step++;
                eps = 9999999;
            }
            else {
                x = (*beta) + (*this) * x_previous;
                for (int i = 0; i < n; i++) {
                    eps = eps + pow((x.mt[i][0] - x_previous.mt[i][0]), 2);
                }
                eps = sqrt(eps);
                cout << "x(" << step++ << "):\n";
                for (int i = 0; i < n; i++) {
                    cout << x_previous.mt[i][0] << endl;
                }
                cout << "e: " << eps << endl;
                x_previous = x;
            }
        } while (eps > e);
        cout << "x(" << step++ << "):\n";
        for (int i = 0; i < n; i++) {
            cout << x_previous.mt[i][0] << endl;
        }
    }
    void SeidelMethod(Matrix* beta, double e, Matrix C, Matrix IB, Matrix IB1) {
        int step = -1;
        Matrix x(n, 1);
        Matrix x_previous(n, 1);
        for (int i = 0; i < n; i++) {
            x.mt[i][0] = 0;
            x_previous.mt[i][0] = 0;
        }
        double eps;
        do {
            eps = 0;
            if (step == -1) {
                x = (*beta);
                x_previous = x;
                step++;
                eps = 9999999;
            }
            else {
                x = IB1 * C * xPrev + IB1 * (*beta);
                for (int i = 0; i < n; i++) {
                    eps = eps + pow((x.mt[i][0] - x_previous.mt[i][0]), 2);
                }
                eps = sqrt(eps);
                cout << "x(" << step++ << "):\n";
                for (int i = 0; i < n; i++) {
                    cout << x_previous.mt[i][0] << endl;
                }
                cout << "e: " << eps << endl;
                x_previous = x;
            }
        } while (eps > e);
        cout << "x(" << step++ << "):\n";
        for (int i = 0; i < n; i++) {
            cout << x_previous.mt[i][0] << endl;
        }
    }
    Matrix Inverse() {
        Matrix M(n, 2 * m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 2 * m; j++) {
                if (j < m) {
                    M.mt[i][j] = mt[i][j];
                }
                else {
                    if (j - m == i) {
                        M.mt[i][j] = 1;
                    }
                    else {
                        M.mt[i][j] = 0;
                    }
                }
            }
        }
        int c = 0;
        int r = 1;
        for (int k = 0; k < (n * (n - 1)) / 2; k++) {
            double t = M.mt[r][c] / M.mt[c][c];
            for (int i = 0; i < 2 * m; i++) {
                M.mt[r][i] = M.mt[r][i] - M.mt[c][i] * t;
            }
            if (r != n - 1) {
                r++;
            }
            else {
                c++;
                r = c + 1;
            }
        }
        c = n - 1;
        r = c - 1;
        for (int k = 0; k < (n * (n - 1)) / 2; k++) {
            double t = M.mt[r][c] / M.mt[c][c];
            for (int i = 0; i < 2 * m; i++) {
                M.mt[r][i] = M.mt[r][i] - M.mt[c][i] * t;
            }
            if (r != 0) {
                r--;
            }
            else {
                c--;
                r = c - 1;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                M.mt[i][j + m] /= M.mt[i][i];
            }
        }
        Matrix Nn, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                N.mt[i][j] = M.mt[i][j + m];
            }
        }
        return N;
    }
    void LowerTriangular(Matrix alpha) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i > j) {
                    mt[i][j] = alpha.mt[i][j];
                }
                else {
                    mt[i][j] = 0;
                }
            }
        }
    }
    void doIdentity() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    mt[i][j] = 1;
                }
                else {
                    mt[i][j] = 0;
                }
            }
        }
    }
    void UpperTriangular(Matrix alpha) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i < j) {
                    mt[i][j] = alpha.mt[i][j];
                }
                else {
                    mt[i][j] = 0;
                }
            }
        }
    }


    ~Matrix() {
        for (int i = 0; i < n; i++) {
            delete[] mt[i];
        }
        delete[] mt;
    }

};

int main() {
    int nA,nB;
    double e;
    cin >> nA;
    Matrix A(nA, nA);
    cin >> A;

    cin >> nB;
    Matrix b(nA, 1);
    cin >> b;

    cin >> e;

    if (!A.CheckApplicable()) {
        cout << "The method is not applicable!";
    }
    else {
        Matrix alpha = A;
        Matrix beta = b;
        alpha.divide(&beta);
        cout << "alpha:\n" << alpha;
        cout << "beta:\n" << beta;
        alpha.JacobiMethod(&beta, e);
    }
    // If it is we find x using Seidel method
    /*else {
        // Make matrix alpha eaual to A and matrix beta equal to b
        Matrix alpha = A;
        Matrix beta = b;

        // Find corresponding numbers in mutrices alpha and beta
        alpha.divide(&beta);
        // Output matrices alpha and beta
        cout << "beta:\n" << beta;
        cout << "alpha:\n" << alpha;

        // Create identity matrix
        Matrix I(nA, nA);
        I.doIdentity();

        // Create matrix B and make it lowertriangular part of matrix alpha
        Matrix B(nA, nA);
        B.LowTr(alpha);
        cout << "B:\n" << B;

        // Create matrix C and make it uppertriangular part of matrix alpha
        Matrix C(nA, nA);
        C.UpTr(alpha);
        cout << "C:\n" << C;

        // Find matrix I-B
        Matrix IB = I - B;
        cout << "I-B:\n" << IB;

        // Find matrix (I-B)^(-1)
        Matrix IB1 = IB.Inverse();
        cout << "(I-B)^-1:\n" << IB1;

        // Solve the equations
        alpha.SeidelMethod(&beta, e, C, IB, IB1);
    }*/
}
