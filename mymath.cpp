#include <vector>
#include "mymath.h"

namespace mymath {
double deriv_h = 1e-3;
double solve_h = 1e-5;
double solve_t = 1e-10;
double integ_n = 100;
};

using mymath::deriv_h;
using mymath::solve_t;
using mymath::integ_n;
using mymath::solve_h;

//корень уравнения
double mymath::solve(double x, double (*f)(double, void*), void* args) {
    double val;
    while (fabs(val = f(x, args)) > solve_t) {
        x -= val / ((f(x + solve_h, args) - f(x - solve_h, args)) / (2 * solve_h));
    }
    return x;
}

//производная функции
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
double mymath::integ(double l, double r, double (*f)(double, void*), void* args) {
    const double t = (r - l) / integ_n,
        t1 = 0.5 * t;
    double res = 0, dx;
    for (double x = l + t1; x < r; x += t) {
        dx = 0.93246951420257751 * t1;
        res += 0.17132449238057801 * (f(x - dx, args) + f(x + dx, args));
        dx = 0.66120938646396499 * t1;
        res += 0.36076157304955814 * (f(x - dx, args) + f(x + dx, args));
        dx = 0.23861918608139146 * t1;
        res += 0.4679139345698638 * (f(x - dx, args) + f(x + dx, args));
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
/*
using dbvec = std::vector<double>;

//производная функции
double mymath::deriv(dbvec& X, double (*f)(dbvec&), int ind, double dlt) {
    const double arr[3] = {
        0.01171875,
        -0.16276041666666666,
        2.9296875,
    };
    double sum = 0;
    for (char i = 0; i < 3; i++) {
        double dx = (1 - 0.4 * i) * dlt;
        X[ind] += dx;
        double r = f(X);
        X[ind] -= 2 * dx;
        r -= f(X);
        sum += arr[i] * r;
    }
    return sum / dlt;
}

//нахождение корня уравнения
double mymath::solve(dbvec X, double (*f)(dbvec&), int ind, double t) {
    const double t1 = 2 * t;
    while (fabs(f(X)) > t) {
        X[ind] += X[ind] * t;
        double r = f(X);
        X[ind] -= X[ind] * t1;
        r -= f(X);
        X[ind] += X[ind] * t;
        r = t1 * f(X) / r;
        x -= 2 * t * f(x) / (f(x + t) - f(x - t));
    }
    return x;
}

//интеграл функции
double integ1(double x, double t, double (*f)(double)) {
    double sum = 0, dx;
    dx = 0.93246951420257751 * t;
    sum += 0.17132449238057801 * (f(x - dx) + f(x + dx));
    dx = 0.66120938646396499 * t;
    sum += 0.36076157304955814 * (f(x - dx) + f(x + dx));
    dx = 0.23861918608139146 * t;
    sum += 0.4679139345698638 * (f(x - dx) + f(x + dx));
    return sum;
}

double mymath::integ(double l, double r, double (*f)(double), int n) {
    const double t = (r - l) / n, t1 = 0.5 * t;
    double res = 0;
    for (double x = l + t1; x < r; x += t) {
        res += integ1(x, t1, f);
    }
    return t1 * res;
}

//решение СЛАУ
int cols;

void convert(dbvec& matr, int i, int j) {
    const double x = matr[j * cols + i] / matr[i * (cols + 1)];
    for (int k = 0; k < cols; k++) {
        matr[j * cols + k] -= x * matr[i * cols + k];
    }
}

void mymath::slae(void* pmatr) {
    dbvec& matr = *static_cast<dbvec*>(pmatr);
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
}*/
