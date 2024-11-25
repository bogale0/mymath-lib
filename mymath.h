#ifndef MYMATH_H
#define MYMATH_H

#include <cmath>
#include <vector>

namespace mymath {
    double deriv_h = 1e-5;
    template <typename Func, typename... Args>
    double deriv(double, Func, Args...);

    double solve_t = 1e-10;
    template <typename Func, typename... Args>
    double solve(double, Func, Args...);

    double integ(double, double, double (*)(double), int = 100);

    void slae(std::vector<double>&);
};

#endif //MYMATH_H
