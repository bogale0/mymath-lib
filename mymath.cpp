#include <vector>
#include <mymath.h>

using mymath::deriv_h;
using mymath::solve_t;
using mymath::integ_n;
using mymath::solve_h;

//корень уравнения
__attribute__((visibility("default")))
double mymath::solve(double x, double (*f)(double, void*), void* args) {
    double val;
    while (fabs(val = f(x, args)) > solve_t) {
        x -= 2 * solve_h * val / (f(x + solve_h, args) - f(x - solve_h, args));
    }
    return x;
}

//производная функции
__attribute__((visibility("default")))
double mymath::deriv(double x, double (*f)(double, void*), void* args) {
    double sum = 0, dx;
    dx = deriv_h;
    sum += 0.01171875 * (f(x + dx, args) - f(x - dx, args));
    dx = 0.6 * deriv_h;
    sum += -0.16276041666666666 * (f(x + dx, args) - f(x - dx, args));
    dx = 0.2 * deriv_h;
    sum += 2.9296875 * (f(x + dx, args) - f(x - dx, args));
    return sum / deriv_h;
}

//интеграл функции
__attribute__((visibility("default")))
double mymath::integ(double l, double r, double (*f)(double, void*), void* args) {
    const double t = (r - l) / integ_n,
        t1 = 0.5 * t;
    double res = 0, dx;
    l += t1;
    for (int i = 0; i < integ_n; i++) {
        dx = 0.93246951420257751 * t1;
        res += 0.17132449238057801 * (f(l - dx, args) + f(l + dx, args));
        dx = 0.66120938646396499 * t1;
        res += 0.36076157304955814 * (f(l - dx, args) + f(l + dx, args));
        dx = 0.23861918608139146 * t1;
        res += 0.4679139345698638 * (f(l - dx, args) + f(l + dx, args));
        l += t;
    }
    return t1 * res;
}

//решение СЛАУ
int cols;

void convert(std::vector<double>& matr, int i, int j) {
    const double x = matr[j * cols + i] / matr[i * (cols + 1)];
    for (int k = 0; k < cols; k++) {
        matr[j * cols + k] -= x * matr[i * cols + k];
    }
}

__attribute__((visibility("default")))
void mymath::slae(void* pmatr) {
    std::vector<double>& matr = *static_cast<std::vector<double>*>(pmatr);
    const int rows = sqrt(matr.size());
    cols = rows + 1;
    for (int i = 0; i < rows; i++) {
        for (int j = rows - 1; j > i; j--) {
            convert(matr, i, j);
        }
    }
    for (int i = rows - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            convert(matr, i, j);
        }
    }
    for (int i = 0; i < rows; i++) {
        matr[i] = matr[i * cols + rows] / matr[i * (cols + 1)];
    }
    matr.resize(rows);
}
