#include <stdio.h>
#include <math.h>
#include "math_funcs.h"

int main() {
    double eps = 1e-5;
    double x = 0.375;
    // Тестируем функции
    printf("f1(1.0) = %f\n", f1(x));
    printf("f2(1.0) = %f\n", f2(x));
    printf("f3(1.0) = %f\n", f3(x));

  printf("f1'(1.0) = %f\n", f1_diff(x));
    printf("f2'(1.0) = %f\n", f2_diff(x));
    printf("f3'(1.0) = %f\n", f3_diff(x));
    
  double value = calculate_area(eps);
    printf("Calculated area: %f\n", value);
    return 0;
}
