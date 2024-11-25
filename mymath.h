#ifndef MYMATH_H
#define MYMATH_H

#include <cmath>

namespace mymath {
double deriv_h = 1e-3;
double solve_h = 1e-5;
double solve_t = 1e-10;
int integ_n = 100;
double solve(double, double (*)(double, void*), void* = nullptr);
double deriv(double, double (*)(double, void*), void* = nullptr);
double integ(double, double, double (*)(double, void*), void* = nullptr);
void slae(void*);
};

#endif //MYMATH_H
