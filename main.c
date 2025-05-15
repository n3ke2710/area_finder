#include <stdio.h>
#include <math.h>
#include "math_funcs.c"


double f(double x){
    return x * x - 2;
}

double g(double x){
    return 0;
}

double CalculateArea(double eps) {
    double a = -100000.0;
    double b = 100000.0;

    return (b - a) * root(f, g, a, b, eps);
}

int main() {
    double a = 2;
    double b = 4;
    double eps = 1e-5;
    printf("area: \n");
    printf("%f\n", integral(f, a, b, eps));
    extern double f1(double x);
    extern double f2(double x);
    extern double f3(double x);
    // printf("root: \n");
    // printf("%f\n", root(f1, f2, a, b, eps));
}