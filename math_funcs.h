#ifndef MATH_FUNCS_H
#define MATH_FUNCS_H

// Объявления ассемблерных функций
double f1(double x);
double f2(double x);
double f3(double x);
double f1_diff(double x);
double f2_diff(double x);
double f3_diff(double x);

// Объявления функций для работы с корнями и интегралами
double diff(double (*f)(double), double (*g)(double), double x);
double derivative(double (*f)(double), double x, double h);
double root(double (*f)(double), double (*g)(double), double a, double b, double eps);
double integral(double (*f)(double), double a, double b, double eps);
double calculate_area(double eps);
void test_root(double eps);
void test_integral(double eps);

extern int debug_mode;
extern int test_root_mode;
extern int test_integral_mode;
#endif
