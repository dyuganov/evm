//#include <iostream>
//#include <time.h>
//#include <limits>
//
//using namespace std;
//
//size_t N = 0;
//
//void initArray(size_t* array, size_t fragments, size_t offset, size_t size) {
//
//    for (int i = 0; i < offset * N; ++i) array[i] = 0;
//
//    for (size_t i = 0; i < size / N; ++i) {
//        for (size_t j = 0; j < N; ++j) {
//            array[offset * j + i] = offset * (j + 1) + i;//filling frags from the first one, it starts with n-1 frags 
//        }
//        array[offset * (N - 1) + i] = i + 1;//then here fills last one 
//    }
//    array[offset * (N - 1) + (size / N) - 1] = 0; // last elem goes into last frag as 0
//
//}
//
//
//
//
//int main() {
//    
//    cin >> N;
//
//    size_t offset = 4 * 1024 * 1024; //16 MB 
//    size_t size = 3.5 * 1024 * 1024; //14 MB 
//
//    size_t* arr = new size_t[N * offset];
//
//   // double ticks = numeric_limits<double>::max();
//
//    for (size_t i = 1; i <= 50; ++i) {
//        initArray(arr, N, offset, size);
//        cout << "fragments: " << i << endl;
//
//        clock_t start = clock();
//
//        for (size_t i = 0, k = 0; i < size; ++i) {
//            k = arr[k];
//        }
//
//        clock_t end = clock();
//        double ticks = (end - start);
//
//        cout << "tacts: " << ticks  << endl;
//        cout << endl;
//
//    }
//
//    delete[] arr;
//
//	return 0;
//}

#include <iostream>
#include <ostream> 
#include <fstream> 
#include <time.h>
#include <limits>
using namespace std; 

const int SIZE = 3.5*1024*1024/ 32; //14 MB 
const int OFFSET = 4*1024*1024 /32; //16 MB 

double test(int N){ // N - number of fragments 

	int* arr = new int[OFFSET * N]; // arr with elements on weight of 16 mB 

	for (int i = 0; i < OFFSET * N; ++i) arr[i] = 0; 
	for (int i = 0; i < (SIZE / N); ++i) { // fill arr to ( indent / count) 
		for (int j = 0; j < N - 1; ++j) { 
			arr[OFFSET * j + i] = OFFSET * (j + 1) + i;//filling frags from the first one, it starts with n-1 frags 
		} 
		arr[OFFSET * (N - 1) + i] = i + 1;//then here fills last one 
	} 
	arr[OFFSET * (N - 1) + (SIZE / N) - 1] = 0; // last elem goes into last frag as 0 

	
	double tmp, ticks = numeric_limits<double>::max();
	for (int i = 0; i < 50; ++i) { 

		clock_t start1 = clock();

		for (unsigned long j = 0, k = 0; j < SIZE; j++) // detour of all elements in all fragments 
			k = arr[k]; 
		clock_t end1 = clock();
		tmp = (end1 - start1);

		if (tmp < ticks) //looking for the least amount of time 
			ticks = tmp; 
	} 
	delete[] arr; 
	return ticks; 
} 

int main(){ 
	int mas[65]; 
	for (auto &i : mas) i = 0; 

	for (int i = 1; i <= 64; ++i) {
		double res = test(i);
		std::cout << res << endl; //commended - another option for easy-making graph in excel 
	}

	return 0; 
}