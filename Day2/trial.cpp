#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img;

	img(500, 500, CV_8UC1, Scalar(0));
	namedWindow("win", WINDOW_NORMAL);
	imshow("win", img);
}