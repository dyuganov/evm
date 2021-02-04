#include <iostream>
#include <ctime>
#include <stdlib.h> // atoi
#include <set>
#include <stdio.h>
#include <time.h>

using namespace std;

void straight(size_t* arr, const size_t& N) {
	for (size_t i = 0; i < N - 1; ++i) {
		arr[i] = i + 1;
	}
	arr[N - 1] = 0;
}

void reversed(size_t* arr, const size_t& N) {
	for (size_t i = N - 1; i > 0; --i) {
		arr[i] = i + 1;
	}
	arr[0] = N - 1;
}

void random(size_t* arr, const size_t& N) {

	size_t* tmp = new size_t[N];
	for (size_t i = 0; i < N; ++i) {
		tmp[i] = i;
	}

	srand(time(NULL));
	for (size_t i = N - 1; i > 1; --i) {
		std::swap(tmp[i], tmp[rand() % i]);
	}

	for (size_t i = 0; i < N - 1; ++i) {
		arr[tmp[i]] = tmp[i + 1];
	}

	arr[tmp[N - 1]] = tmp[0];

	delete[] tmp;
}

void warmup(size_t* arr, const size_t& N, const size_t& K) {
	size_t tmp = 0;
	for (size_t i = 0; i < N * K; ++i) {
		tmp = arr[tmp];
	}
}

int main(int argc, char** argv) {

	size_t N = 0, K = 0;
	N = atoi(argv[1]);
	K = atoi(argv[2]);

	//cin >> N;
	//cin >> K;
	size_t* arr = new size_t[N];

	//Straight acces array
	cout << endl << "Straight acces array" << endl;
	straight(arr, N);
	warmup(arr, N, K);
	clock_t start1 = clock();

	for (size_t i = 0, k = 0; i < N * K; ++i) {
		k = arr[k];
	}

	clock_t end1 = clock();
	double ticks = (end1 - start1);
	printf("Time taken: %d ticks.\n", ticks / (K * N));

	//Reversed acces array
	cout << endl << "Reversed acces array" << endl;
	reversed(arr, N);
	warmup(arr, N, K);
	clock_t start2 = clock();

	for (size_t i = 0, k = 0; i < N * K; ++i) {
		k = arr[k];
	}

	clock_t end2 = clock();
	ticks = (end2 - start2);
	printf("Time taken: %d ticks.\n", ticks / (K * N));

	// Random acces array v1
	cout << endl <<"Random acces array" << endl;
	random(arr, N);
	warmup(arr, N, K);
	clock_t start3 = clock();

	for (size_t i = 0, k = 0; i < N * K; ++i) {
		k = arr[k];
	}

	clock_t end3 = clock();
	ticks = (end3 - start3);
	printf("Time taken: %d ticks.\n", ticks / (K * N));


	delete[] arr;

	return 0;
}
