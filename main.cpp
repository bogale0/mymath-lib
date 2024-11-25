#include <iostream>
#include <mymath.h>
#include <vector>
#include <ctime>
using std::cout;
using std::cin;
using std::endl;

double f1(double x, void* y) {
    if (y)
        return pow(x, 3) - *static_cast<double*>(y);
    else
        return pow(x, 3);
}

double f2(double x, void* y) {
    if (y)
        return exp(x) - *static_cast<double*>(y);
    else
        return exp(x);
}

double f3(double x, void* y) {
    if (y)
        return 20 * sin(x) - *static_cast<double*>(y);
    else
        return 20 * sin(x);
}

double f4(double x, void* y) {
    if (y)
        return log(x) + *static_cast<double*>(y);
    else
        return log(x);
}

int main() {
    srand(time(nullptr));
    std::vector<double> res(12);
    const int N = 1000;
    for (int i = 0; i < N; i++) {
        double x = 1 + rand() * 10. / RAND_MAX;
        res[0] += fabs(mymath::deriv(x, f1) / (3 * x * x) - 1);
        res[1] += fabs(mymath::deriv(x, f2) / exp(x) - 1);
        res[2] += fabs(mymath::deriv(x, f3) / (20 * cos(x)) - 1);
        res[3] += fabs(mymath::deriv(x, f4) * x - 1);
        res[4] += fabs(mymath::integ(1, x, f1) * 4 / (pow(x, 4) - 1) - 1);
        res[5] += fabs(mymath::integ(1, x, f2) / (exp(x) - M_E) - 1);
        res[6] += fabs(mymath::integ(1, x, f3) / 20 / (cos(1) - cos(x)) - 1);
        res[7] += fabs(mymath::integ(1, x, f4) / (x * (log(x) - 1) + 1) - 1);
        res[8] += fabs(mymath::solve(3, f1, &x) / pow(x, 1. / 3) - 1);
        res[9] += fabs(mymath::solve(1, f2, &x) / log(x) - 1);
        res[10] += fabs(mymath::solve(1, f3, &x) - asin(x / 20));
        res[11] += fabs(mymath::solve(1e-3, f4, &x) * exp(x) - 1);
    }
    for (double r : res) {
        cout << r / N << endl;
    }
}
