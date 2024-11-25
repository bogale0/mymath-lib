#ifndef MYMATH_H
#define MYMATH_H

#include <cmath>

namespace mymath {
    double deriv_h;// = 1e-5;
    template <typename Func, typename... Args>
    double deriv(double, Func, Args...);

    double solve_t;// = 1e-10;
    template <typename Func, typename... Args>
    double solve(double, Func, Args...);

    double integ_n;// = 100;
    template <typename Func, typename... Args>
    double integ(double, double, Func, Args...);

    void slae(void*);
};

#endif //MYMATH_H
