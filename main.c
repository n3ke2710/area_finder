#include <stdio.h>
#include <math.h>
#include <string.h>
#include "math_funcs.h"

void print_help() {
    printf("Доступные ключи командной строки:\n");
    printf("  --help    - показать эту справку\n");
    printf("  --eps     - задать точность вычислений (по умолчанию 1e-5)\n");
    printf("  --x       - задать значение x для тестирования функций (по умолчанию 0.375)\n");
    printf("  --test    - включить режим отладки с подробным выводом\n");
    printf("  --test_root - тестировать нахождение корней\n");
    printf("  --test_integral - тестировать нахождение интеграла\n");
    printf("\nФункции math_funcs:");
    printf("  root            - находит точки пересечения двух функций");
    printf("  integral        - находит интеграл функции на отрезке");
    printf("  calculate_area  - находит площадь заданной фигуры");
}

int main(int argc, char *argv[]) {
    double eps = 1e-5;
    double x = 0.375;


    // Обработка аргументов командной строки
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        } else {
            if (strcmp(argv[i], "--test") == 0) {
                debug_mode = 1;
            }
            if (strcmp(argv[i], "--test_root") == 0) {
			    test_root_mode = 1;
            } 
            if (strcmp(argv[i], "--test_integral") == 0) {
                test_integral_mode = 1;
            }
            if (strcmp(argv[i], "--x") == 0) {
                x = atof(argv[i+1]);
            }
            if (strcmp(argv[i], "--eps") == 0) {
                eps = atof(argv[i+1]);
            }
            if (strcmp(argv[i], "--test_iterations") == 0) {
                test_iterations_mode = 1;
            }
        }
    }

    if (test_root_mode) {
        test_root(eps);
        return 0;
    }
    if (test_integral_mode) {
        test_integral(eps);
        return 0;
    }
    // Тестируем функции
    if (debug_mode) {
        printf("f1(%.3f) = %f\n", x, f1(x));
        printf("f2(%.3f) = %f\n", x, f2(x));
        printf("f3(%.3f) = %f\n", x, f3(x));

        printf("f1'(%.3f) = %f\n", x, f1_diff(x));
        printf("f2'(%.3f) = %f\n", x, f2_diff(x));
        printf("f3'(%.3f) = %f\n", x, f3_diff(x));
    }
    
    double value = calculate_area(eps);
    printf("Calculated area: %f\n", value);
    return 0;
}
