#include <iostream>
#include "mymath.h"
#include <vector>
#include <ctime>
using std::cout;
using std::cin;
using std::endl;

double func(double x, double z) {
    return log(x) - z;
}

double func1(double x) {
    return log(x);
}

int main()
try {
    mymath::deriv_h = 1e-5;
    mymath::solve_t = 1e-10;
    mymath::integ_n = 100;
    srand(time(nullptr));
    for (int i = 0; i < 10; i++) {
        double x = rand() * 10. / RAND_MAX, y = x + 6;
        if (fabs(mymath::deriv(x, func1, y) * x - 1) > 1e-10) throw 1;
        if (fabs(mymath::integ(1, y, func1) / (y * (log(y) - 1) + 1) - 1) > 1e-10) throw 2;
        if (fabs(mymath::solve(0, func, y) / exp(y) - 1) > 1e-10) throw 4;
    }
    std::vector<double> v {3,2,-5,-1,2,-1,3,13,1,2,-1,9};
    mymath::slae(&v);
    if (fabs(v[0] - 3) + fabs(v[1] - 5) + fabs(v[2] - 4) > 1e-10) throw 8;
    cout << "Success" << endl;
} catch(int err) {
    cout << "Err: " << err << endl;
}
/*
    cout << "Интеграл ln(x), a=0, b=1: " << mymath::integ(0, 1, log) << endl;
    cout << "Корень ln(x)=1: " << mymath::solve(2, func) << endl;
    cout << v[0] << ", " << v[1] << ", " << v[2] << endl;
*/
