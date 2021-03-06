#include <iostream>
#include <cmath>
#include <memory.h>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define N (2028) // размерность матрицы
#define M (10) // количество членов ряда (итераций)

void matrixSum (float* first, float* second, float* result) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result[i * N + j] = first[i * N + j] + second[i * N + j];
        }
    }
}

void matrixSub (float* first, float* second, float* result) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result[i * N + j] = first[i * N + j] - second[i * N + j];
        }
    }
}

void matrixMult(float* first, float* second, float* result) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result[i * N + j] = 0;
            for (int k = 0; k < N; ++k) {
                result[i * N + j] += first[i * N + k] * second[k * N + j];
            }
        }
    }
}


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
    float* B = (float*)calloc(N * N, sizeof(float)); // A(�) / a_1 * a_inf
    float* I = (float*)calloc(N * N, sizeof(float)); // ��������� �������
    float* BA = (float*)calloc(N * N, sizeof(float)); // B * A
    float* R = (float*)calloc(N * N, sizeof(float)); // I - BA
    float* res = (float*)calloc(N * N, sizeof(float)); // result
    float* buf = (float*)calloc(N * N, sizeof(float)); // buffer

    // ����. ����� �� �������� � �������
    float a_1 = A_1(A);
    float a_inf = A_inf(A);

    // ���������� ��������� �������
    IMatrixFill(I);
    IMatrixFill(buf); // ���� ���������, ����� � ��� ��������� �������� ��������

    // B
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            B[i * N + j] = A[j * N + i] / (a_inf * a_1);
        }
    }

    // R
    matrixMult(A, B, BA);
    matrixSub(I, BA, R);

    for (int k = 0; k < M - 1; ++k) {
        matrixMult(I, R, BA);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                I[i * N + j] = BA[i * N + j];
            }
        }
        matrixSum(buf, I, buf);
    }
    matrixMult(buf, B, res);

    free(B);
    free(BA);
    free(I);
    free(R);
    free(buf);
    return res;
}


int main()
{
    float* A = (float*)calloc(N * N, sizeof(float)); // original matrix
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
    free(A);
    free(Inv);

    return 0;
}
