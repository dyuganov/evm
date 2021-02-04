#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

#ifdef __INTEL_COMPILER
#include <mkl_cblas.h>
#else
#include <cblas.h>
#endif

using namespace std;

#define N (2028) // размерность матрицы
#define M (10) // количество членов ряда (итераций)

float A_1(float* A) {
    float max = 0, tmp = 0;
    for (int i = 0; i < N; ++i) {
        tmp = 0;
        for (int j = 0; j < N; ++j) {
            tmp += abs(A[i * N + j]);
        }
        if (tmp > max) max = tmp;
    }
    return max;
}

float A_inf(float* A) {
    float max = 0, tmp = 0;
    for (int i = 0; i < N; ++i) {
        tmp = 0;
        for (int j = 0; j < N; ++j) {
            tmp += abs(A[j * N + i]);
        }
        if (tmp > max) max = tmp;
    }
    return max;
}

void IMatrixFill(float* I) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            I[i * N + j] = (i == j);
        }
    }
}

float* invertMatrix(float* A) {
    float* I = new float[N * N]; // единичная матрица
    float* R = new float[N * N]; // I - BA
    float* tmp1 = new float[N * N];
    float* tmp2 = new float[N * N];

    float* res = new float[N * N]; // result -- его не удалять.

    // макс. сумма по столбцам и строкам
    float a_1 = A_1(A);
    float a_inf = A_inf(A);

    // заполнение единичной матрицы
    IMatrixFill(I);
    IMatrixFill(res);
    IMatrixFill(tmp1);
    IMatrixFill(tmp2);

    cblas_sgemm(CblasRowMajor, CblasTrans, CblasNoTrans, N, N, N, -1.0 / (a1 * a8), A, N, A, N, 1.0, R, N);

    for (int k = 0; k < M - 1; ++k) {
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0, TMP, N, R, N, 0.0, TMP2, N);
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1.0, I, N, TMP2, N, 0.0, TMP, N);
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0, I, N, TMP, N, 1.0, INV, N);
    }
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1.0 / (max_l * max_c), INV, N, A, N, 0.0, INV, N);



    delete[](tmp1);
    delete[](tmp2);
    delete[](I);
    delete[](R);
    return res;
}


int main()
{
    float* A = new float[N * N]; // original matrix
    float* Inv;

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            A[i * N + j] = (i == j);
            //std::cout << A[i * N + j] << ' ';
        }
        //std::cout << std::endl;
    }
    //std::cout << std::endl;
    //std::cout << std::endl;

    Inv = invertMatrix(A);

    /*
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            std::cout << Inv[i * N + j] << ' ';
        }
        std::cout << std::endl;
    }
    */
    delete[](A);
    delete[](Inv);

    return 0;
}
