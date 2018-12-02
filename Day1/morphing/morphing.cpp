#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat img1, img2;
int rows;
int cols;

void updateFun(int t, void *)
{
	Mat morphed(rows, cols, CV_8UC3, Scalar(0));

	for(int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
			for(int k = 0; k < 3; k++)
			{
				float a = (float)((t * 1.0) / 100);
				float b = 1 - a;
				float c = ((float)img1.at<Vec3b>(i , j)[k]) * a;
				float d = ((float)img2.at<Vec3b>(i , j)[k]) * b;

				morphed.at<Vec3b>(i , j)[k] = (int)(c + d);
			}

	imshow("win", morphed);
}

int main()
{
	int t = 0;

	img1 = imread("image1.jpg", 1);
	img2 = imread("image2.jpg", 1);
	rows = img1.rows;
	cols = img1.cols;
	
	cout << "rows = " << rows << ", coloumns = " << cols << "\n";

	namedWindow("win", WINDOW_NORMAL);

	createTrackbar("tb", "win", &t, 100, updateFun);
	waitKey(0);
	return 0;
}