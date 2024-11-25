#ifndef MYMATH_H
#define MYMATH_H

#include <cmath>

namespace mymath {
double solve(double, double (*)(double, void*), void* = nullptr);
double deriv(double, double (*)(double, void*), void* = nullptr);
double integ(double, double, double (*)(double, void*), void* = nullptr);
void slae(void*);
};

#endif //MYMATH_H
