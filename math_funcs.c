#include <math.h>
#include <stdio.h>

int debug_mode = 0;

extern double f1(double x);
extern double f2(double x);
extern double f3(double x);

extern double f1_diff(double x);
extern double f2_diff(double x);
extern double f3_diff(double x);

double derivative(double (*f)(double), double x, double h) {
    return (f(x + h) - f(x - h)) / (2 * h);
}

double root(double (*f)(double), double (*g)(double), double (*df)(double), double (*dg)(double), double a, double b, double eps) {
    double x = (a + b) / 2;
    for (int i = 0; i < 100; i++) {
        if (debug_mode) {
            printf("x = %f, ", x);
        }
        double f_res = f(x);
        double g_res = g(x);
        if (debug_mode) {
            printf("g_res = %f, ", g_res);
        }
        double current_diff = f_res - g_res;
        if (fabs(current_diff) < eps) {
            return x;
        }
        if (debug_mode) {
            printf("current_diff = %f, ", current_diff);
        }

        double df_res = df(x);
        double dg_res = dg(x);
        double derivative_val = df_res - dg_res;
        if (debug_mode) {
            printf("df_res = %f, ", df_res);
            printf("dg_res = %f, ", dg_res);
            printf("derivative_val = %f, ", derivative_val);
        }
        
        if (fabs(derivative_val) < eps * eps) {
            break;
        }
        
        double x_temp = current_diff / derivative_val;
        if (debug_mode) {
            printf("x_temp = %f, ", x_temp);
        }
        double x_new = x - x_temp;
        if (x_new < a) x_new = a;
        if (x_new > b) x_new = b;
        
        if (fabs(x_new - x) < eps) {
            return x_new;
        }
        
        x = x_new;
        if (debug_mode) {
            printf("x = %f\n", x);
        }
    }
    
    return x;
}

double integral(double (*f)(double), double a, double b, double eps) {
    double sum = 0;
    int n = 2 * (b - a) / eps;
    double h = (b - a) / n;

    for (int i = 0; i < n; i++) {
        double x1 = a + i * h;
        double x2 = x1 + h;
        double y1 = f(x1);
        double y2 = f(x2);
        
        if (isnan(y1)) {
            if (debug_mode) {
                printf("Warning: NaN in integral at x1=%f\n", x1);
            }
            return NAN;
        }
        if (isnan(y2)) {
            if (debug_mode) {
                printf("Warning: NaN in integral at x2=%f\n", x2);
            }
            return NAN;
        }
        
        sum += (y1 + y2) * h / 2;
    }

    return sum;
}

double calculate_area(double eps) {
    if (debug_mode) {
        printf("\nf1 and f2\n");
    }
    double x1 = root(f2, f1, f2_diff, f1_diff, 0, 1, eps);
    if (debug_mode) {
        printf("\nf2 and f3\n");
    }
    double x2 = root(f2, f3, f2_diff, f3_diff, -2, 1, eps);
    if (debug_mode) {
        printf("\nf1 and f3\n");
    }
    double x3 = root(f1, f3, f1_diff, f3_diff, -2, -1.5, eps);

    // Sort the roots so x1 < x2 < x3
    double temp;
    if (x1 > x2) { temp = x1; x1 = x2; x2 = temp; }
    if (x1 > x3) { temp = x1; x1 = x3; x3 = temp; }
    if (x2 > x3) { temp = x2; x2 = x3; x3 = temp; }
    
    if (debug_mode) {
        printf("\n");
        printf("%f %f %f\n", x1, x2, x3);
    }

    // Calculate the area between the curves
    double inter1_area1 = integral(f1, x1, x2, eps);
    double inter2_area1 = integral(f3, x1, x2, eps);
    double inter1_area2 = integral(f1, x2, x3, eps);
    double inter2_area2 = integral(f2, x2, x3, eps);
    if (debug_mode) {
        printf("%f, %f, %f, %f\n", inter1_area1, inter2_area1, inter1_area2, inter2_area2);
    }
    double area1 = inter1_area1 - inter2_area1;
    double area2 = inter1_area2 - inter2_area2;

    return fabs(area1) + fabs(area2);
}
