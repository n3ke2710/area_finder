#include <math.h>

double diff(double (*f)(double), double (*g)(double), double x) {
    return f(x) - g(x);
}

double derivative(double (*f)(double), double x, double h) {
    return (f(x + h) - f(x - h)) / (2 * h);
}

double root(double (*f)(double), double (*g)(double), double a, double b, double eps) {
    double h = eps/2; 
    double x = (a + b) / 2;

    for (int i = 0; i < 100; i++) {
        double current_diff = diff(f, g, x);
        if (fabs(current_diff) < eps) {
            return x;
        }
        
        double df = derivative(f, x, h);
        double dg = derivative(g, x, h);
        double derivative_val = df - dg;
        
        if (fabs(derivative_val) < eps * eps) {
            break;
        }
        
        double x_new = x - current_diff / derivative_val;
        
        if (x_new < a) x_new = a;
        if (x_new > b) x_new = b;
        
        if (fabs(x_new - x) < eps) {
            return x_new;
        }
        
        x = x_new;
    }
    
    return x;
}

double integral(double (*f)(double), double a, double b, double eps) {
    double sum = 0.0;
    int n = (b - a) / eps;
    double h = (b - a) / n;

    for (int i = 0; i < n; i++) {
        sum += h * (f(a + i * h) + f(a + (i + 1) * h)) / 2;
    }

    return sum;
}