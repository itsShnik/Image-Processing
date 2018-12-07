#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat img;

int* avg(int i, int j, int s)
{
	int *sum = (int* )malloc(sizeof(int) * 3);

	for(int p = s * i; p <= s * i + s - 1; p++)
		for(int q = s * j; q <= s * j + s - 1; q++)
			for(int r = 0; r < 3; r++)
				sum[r] += (img.at<Vec3b>(p, q)[r]) / 4;

	//cout << "sum = " << *(sum + 1) << "\n";
	
	return sum;
}

int main()//reduce by a size of 4
{
	img = imread("Lena.jpg", 1);
	int rows = img.rows;
	int cols = img.cols;

	int s = 2;

	Mat downscaled(rows/s, cols/s, CV_8UC3, Scalar(0));

	for(int i = 0; i < rows/s; i++)
		for(int j = 0; j < cols/s; j++)
		{
			int *p = avg(i , j , s);
			

			cout << "p = " << *(p + 1) << "\n";

			for(int k = 0; k < 3; k++)
			{
				downscaled.at<Vec3b>(i , j)[k] = *(p + k);
			}

			free(p);
		} 

	Mat upscaled(rows, cols, CV_8UC3, Scalar(0));

	for(int i = 0; i < rows / s; i++)
		for(int j = 0; j < cols / s; j++)
		{
			for(int p = s * i; p <= s * i + s - 1; p++)
				for(int q = s * j; q <= s * j + s - 1; q++)
				{	
					cout << "p ,q = " << p << " , " << q << "\n";
					for(int k = 0 ; k < 3; k++)
						upscaled.at<Vec3b>(p , q)[k] = downscaled.at<Vec3b>(i , j)[k];
				}
		}
	
	namedWindow("win", WINDOW_AUTOSIZE);
	namedWindow("win_ds", WINDOW_AUTOSIZE);
	namedWindow("win_us", WINDOW_AUTOSIZE);
	imshow("win", img);
	imshow("win_ds", downscaled);
	imshow("win_us", upscaled);
	waitKey(0);
	return 0;
}