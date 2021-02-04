#include <stdio.h>
#include <math.h>
#include <time.h>

int main(void) {

    double pi = 0;
    int n;
    scanf("%d", &n);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    for(int i = 0; i < n; ++i){
        pi += (4 * pow(-1, i)) / (2 * i + 1); // try  n = 250000000
    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    printf("Time taken: %lf sec.\n", end.tv_sec-start.tv_sec + 0.000000001*(end.tv_nsec-start.tv_nsec));


    printf("%f\n", pi);

    return 0;
}

//  gcc prog.c –o prog -lrt

// а лучше использовать
//  g++ main.c -o prog.out
// и потом
// ./prog.out

//Абсолютная погрешность определяется разницей, например, в
//секундах между временем таймера и точным временем выполнения
//программы. Поскольку точное время выполнения программы никогда не
//известно, то абсолютная погрешность измерения оценивается точностью
//измерительного прибора.

// время - 15 сек, точность - 10^-9 сек (1 мс)

// попробовать еще функцию times и утилиту time
