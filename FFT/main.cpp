#include <iostream>
#include <complex>
#include <cmath>
#include <iterator>
#include <vector>

using namespace std;

typedef complex<double>xy;
const double PI = 3.1415926536;
const int N = 8;

unsigned int Prepare(unsigned int x, int log2n)
{
    int n = 0;
    for (int i = 0; i < log2n; i++) {
        n <<= 1;
        n |= (x & 1);
        x >>= 1;
    }
    return n;
}

template<class Iter_T>
void fft(Iter_T& a, Iter_T& b, int log2n) {

    for (unsigned int i = 0; i < N; i++) {
        int reverse = Prepare(i, log2n);
        b[i] = a[reverse];
    }
    const xy I(0, 1);
    for (int s = 1; s <= log2n; s++) {
        double m = pow(2, s);
        xy wm = exp((-2.0) * PI * I / m);
        for (int k = 0; k < N - 1; k += m) {
            xy w(1, 0);
            for (int j = 0; j < m / 2; j++) {
                xy p = w * b[k + j + m / 2];
                xy q = b[k + j];
                b[k + j] = q + p;
                b[k + j + m / 2] = q - p;
                w = w * wm;
            }
        }
    }
}

int main()
{
    vector<xy> a(N);
    for (int i = 0; i < N; i++) {
        char a1,a2,b1,b2;
        double real, imaginary;
        if (i < N - 1) {
            cin >> a1 >> real >> b1 >> imaginary >> a2 >> b2;
        }
        else {
            cin >> a1 >> real >> b1 >> imaginary >> a2;
        }
        a[i] = xy(real, imaginary);
    }
    vector<xy> b(N);
    fft(a, b, 3);
    for (int i = 0; i < N; i++) {
        if (i < N - 1) {
            cout << b[i] << endl;
        }
        else {
            cout << b[i];
        }
    }
}
