#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;
#ifdef WIN32
#define GNUPLOT_NAME "C:\\gnuplot\\bin\\gnuplot -persist"
#else
#define GNUPLOT_NAME "gnuplot-x11 -persist"
#endif //WIN32
int main()
{
    int N;
    double v0, k0, alpha1, beta1, alpha2, beta2, T, result = 0, x;


    cin >> v0 >> k0 >> alpha1 >> beta1 >> alpha2 >> beta2 >> T >> N;
    double* t = new double[N + 1];
    double* v = new double[N + 1];
    double* k = new double[N + 1];
    x = T / N;

    for (int i = 0; i < N + 1; i++) {
        if (i == 0) {
            t[0] = result;
        }
        else {
            result += x;
            t[i] = result;
        }
    }


    for (int i = 0; i < N + 1; i++) {
        if (i == 0) {
            v[0] = v0;
            k[0] = k0;
            v0 = v0 - alpha2 / beta2;
            k0 = k0 - alpha1 / beta1;
        }
        else {
            v[i] = v0 * cos(sqrt(alpha1 * alpha2) * t[i]) - k0 * sqrt(alpha2) * beta1 / (beta2 * sqrt(alpha1)) * sin(sqrt(alpha1 * alpha2) * t[i]) + alpha2 / beta2;

            k[i] = v0 * sqrt(alpha1) * beta2 / (beta1 * sqrt(alpha2)) * sin(sqrt(alpha1 * alpha2) * t[i]) + k0 * cos(sqrt(alpha1 * alpha2) * t[i]) + alpha1 / beta1;
        }
    }
    cout << "t:\n";
    for (int i = 0; i < N + 1; i++) {
        if (i < N) {
            cout << fixed << setprecision(2) << t[i] << " ";
        }

        else {
            cout << fixed << setprecision(2) << t[i] << endl;
        }
    }
    cout << "v:\n";
    for (int i = 0; i < N + 1; i++) {
        if (i < N) {
            cout << fixed << setprecision(2) << v[i] << " ";
        }
        else {
            cout << fixed << setprecision(2) << v[i] << endl;
        }
    }
    cout << "k:\n";
    for (int i = 0; i < N + 1; i++) {
        if (i < N) {
            cout << fixed << setprecision(2) << k[i] << " ";
        }
        else {
            cout << fixed << setprecision(2) << k[i];
        }
    }
    #ifdef WIN32
    FILE* pipeA = _popen(GNUPLOT_NAME, "w");
    FILE* pipeB = _popen(GNUPLOT_NAME, "w");
#else
    FILE* pipeA = popen(GNUPLOT_NAME, "w");
    FILE* pipeB = popen(GNUPLOT_NAME, "w");
#endif // WIN32
    if (pipeA != NULL && pipeB != NULL) {
        fprintf(pipeA, "%s\n", "plot '-' using 1:2 title 'victims' with lines, '-' using 1:2 title 'killers' with lines");
        for (int i = 0; i < N + 1; i++) {
            fprintf(pipeA, "%f\t%f\n", t[i], v[i]);
        }
        fprintf(pipeA, "%s\n", "e");
        for (int i = 0; i < N + 1; i++) {
            fprintf(pipeA, "%f\t%f\n", t[i], k[i]);
        }
        fprintf(pipeA, "%s\n", "e");
        fflush(pipeA);
        fprintf(pipeB, "%s\n", "plot '-' using 1:2 title 'relation' with lines");
    for (int i = 0; i < N + 1; i++) {
            fprintf(pipeB, "%f\t%f\n", v[i], k[i]);
        }
        fprintf(pipeB, "%s\n", "e");
        fflush(pipeB);

#ifdef WIN32
        _pclose(pipeA);
        _pclose(pipeA);
#else
        pclose(pipeA);
        pclose(pipeB);
#endif // WIN32
    }
    else {
        std::cout << "Could not open pipe" << std::endl;
    }
}
