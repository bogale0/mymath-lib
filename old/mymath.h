#ifndef MYMATH_H
#define MYMATH_H

#include <cmath>

namespace mymath {
	double deriv(double, double (*)(double), double = 1e-3);
	double solve(double, double (*)(double), double = 1e-12);
	double integ(double, double, double (*)(double), int = 100);
	void slae(void*);
};

#endif //MYMATH_H
