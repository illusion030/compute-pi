#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "computepi.h"

#define CLOCK_ID CLOCK_MONOTONIC_RAW
#define ONE_SEC 1000000000.0
#define correct_pi acos(-1.0)

int main(int argc, char const *argv[])
{
    struct timespec start = {0, 0};
    struct timespec end = {0, 0};

    if (argc < 2) return -1;

    int N = atoi(argv[1]);
    int i, loop = 5000;
    double pi, error = 0;

    // Baseline
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        pi = compute_pi_baseline(N);
        error += (pi - correct_pi) > 0
                 ? (pi - correct_pi) / correct_pi
                 : (correct_pi - pi) / correct_pi;
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf %.12f ", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC, error / loop);

    error = 0;

    // OpenMP with 2 threads
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        pi = compute_pi_openmp(N, 2);
        error += (pi - correct_pi) > 0
                 ? (pi - correct_pi) / correct_pi
                 : (correct_pi - pi) / correct_pi;
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf %.12f ", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC, error / loop);

    error = 0;

    // OpenMP with 4 threads
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        pi = compute_pi_openmp(N, 4);
        error += (pi - correct_pi) > 0
                 ? (pi - correct_pi) / correct_pi
                 : (correct_pi - pi) / correct_pi;
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf %.12f ", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC, error / loop);

    error = 0;

    // AVX SIMD
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        pi = compute_pi_avx(N);
        error += (pi - correct_pi) > 0
                 ? (pi - correct_pi) / correct_pi
                 : (correct_pi - pi) / correct_pi;
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf %.12f ", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC, error / loop);

    error = 0;

    // AVX SIMD + Loop unrolling
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        pi = compute_pi_avx_unroll(N);
        error += (pi - correct_pi) > 0
                 ? (pi - correct_pi) / correct_pi
                 : (correct_pi - pi) / correct_pi;
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf %.12f ", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC, error / loop);

    error = 0;

    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        pi = compute_pi_leibniz(N);
        error += (pi - correct_pi) > 0
                 ? (pi - correct_pi) / correct_pi
                 : (correct_pi - pi) / correct_pi;
        clock_gettime(CLOCK_ID, &end);
    }

    printf("%lf %.12f ", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC, error / loop);

    error = 0;

    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        pi = compute_pi_leibniz_avx(N);
        error += (pi - correct_pi) > 0
                 ? (pi - correct_pi) / correct_pi
                 : (correct_pi - pi) / correct_pi;
        clock_gettime(CLOCK_ID, &end);
    }

    printf("%lf %.12f\n", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC, error / loop);

    return 0;
}
