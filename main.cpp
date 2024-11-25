#include <iostream>
#include "mymath.h"
#include <vector>
#include <ctime>
using std::cout;
using std::cin;
using std::endl;

double func(double x, void* z) {
    return log(x) - *static_cast<double*>(z);
}

double func1(double x, void*) {
    return log(x);
}



int main() {
    srand(time(nullptr));
    for (int i = 0; i < 1000; i++) {
        double x = rand() * 10. / RAND_MAX, y = x + 6;
        double res;
        if (fabs(res = mymath::deriv(x, func1) * x - 1) > 1e-10) {
            cout << "Err 1: " << res << endl;
        }
        if (fabs(res = mymath::integ(1, y, func1) / (y * (log(y) - 1) + 1) - 1) > 1e-10) {
            cout << "Err 2: " << res << endl;
        }
        if (fabs(res = mymath::solve(0, func, &y) / exp(y) - 1) > 1e-10) {
            cout << "Err 3: " << res << endl;
        }
    }
    std::vector<double> v {3,2,-5,-1,2,-1,3,13,1,2,-1,9};
    mymath::slae(&v);
}
/*
    cout << "Интеграл ln(x), a=0, b=1: " << mymath::integ(0, 1, log) << endl;
    cout << "Корень ln(x)=1: " << mymath::solve(2, func) << endl;
    cout << v[0] << ", " << v[1] << ", " << v[2] << endl;
*/
