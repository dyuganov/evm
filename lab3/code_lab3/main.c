#include <stdio.h>
#include <math.h>
#include <time.h>

double calculate_pi(const unsigned long n){
  double result = 0;
  for(unsigned long i = 0; i < n; ++i){
      result += (4 * pow(-1, i)) / (2 * i + 1);
  }
  return result;
}

int main(void) {

    double pi = 0;
    unsigned long n;
    scanf("%lu", &n);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    pi = calculate_pi(n);

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    printf("Time taken: %lf sec.\n", end.tv_sec-start.tv_sec + 0.000000001*(end.tv_nsec-start.tv_nsec));

    printf("%f\n", pi);

    return 0;
}
