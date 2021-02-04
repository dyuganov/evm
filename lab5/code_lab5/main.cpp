#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/types_c.h"

#include <ctime>
#include <iostream>

using namespace cv;
using std::cout;
using std::endl;


int main(int argc, char** argv)
{
	
	VideoCapture cam;
	if (!cam.open(0)) return 0;

	long int framesCnt = 0;
	long double totalTime = 0, inputTime = 0, procTime = 0, outputTime = 0;
	
	// ��� ����� ���� �� ����������� �������� c ������
	namedWindow("Esc_checker", cv::WindowFlags::WINDOW_AUTOSIZE); 

	while (1)
	{
		Mat capture;

		clock_t c_start = clock(); // ����� ������ ��������� �����

		cam >> capture;
		
		clock_t c_end = clock(); // ����� ��������� ��������� �����
		double input_time = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC; // ��������� �������� ���������� �������, ������� � �������
		totalTime += input_time;
		inputTime += input_time;
		
		if (capture.empty()) break;

		c_start = clock(); // ������ ������ �������������� �����
		
		// ������� � ���������
		/*
		double alpha = 3.0; // ��������
		int beta = -100;     // �������
		for (int y = 0; y < capture.rows; y++) {
			for (int x = 0; x < capture.cols; x++) {
				for (int c = 0; c < capture.channels(); c++) {
					capture.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha * capture.at<Vec3b>(y, x)[c] + beta);
				}
			}
		}
		*/
		// ����������� �����
		cvtColor(capture, capture, CV_RGB2HLS);

		// ���������
		//flip(capture, capture, 0);
		
		c_end = clock();// ������ ��������� �������������� �����
		double calculations_time = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC; // ��������� �������� ���������� �������, ������� � �������
		totalTime += calculations_time;
		procTime += calculations_time;
		
		c_start = clock(); // ������ ������ ������ �����

		//std::string imgName = "Look at what you've become!";
		imshow("Look at what you've become!", capture);

		c_end = clock(); // ������ ��������� ������ �����
		double timeElapsed2 = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC; // ��������� �������� ���������� �������, ������� � �������
		outputTime += timeElapsed2;

		totalTime += timeElapsed2;
		framesCnt++;

		// ��������� ��� ������� ESC
		if (waitKey(10) == 27) {
			break;
		}
	}

	long double percent = totalTime / 100.0;
	long double totalTime_sec = totalTime / 1000;
	long double input_perc = inputTime / percent;
	long double proc_perc = procTime / percent;
	long double output_perc = outputTime / percent;

	cout << "Total time: " << totalTime_sec << " sec." << endl; // ��� ����� ������ ���������
	cout << "CPU time for reading frames: " << totalTime_sec * input_perc / 100 << " sec. (" << input_perc << "%)" << endl; // ����� �� ������ ������ � �������
	cout << "CPU time for processing frames: " << totalTime_sec * proc_perc / 100 << " sec. (" << proc_perc << "%)" << endl; // ����� �� ��������� ������ � �������
	cout << "CPU time for output frames: " << totalTime_sec * output_perc / 100 << " sec. (" << output_perc << "%)" << endl; // ����� �� ����� ������ � �������
	cout << "Avg. framerate: " << ((framesCnt) / (totalTime / 1000.0)) << " fps." << endl; // ������ � ������� � �������


	return 0;
}
