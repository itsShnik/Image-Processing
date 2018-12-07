//cvtcolor(img1, img2, cv::COLOR_BGR2HSV)
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
#include <cmath>
#include <queue>

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(0);

	Mat img;

	while(1)
	{
		cap >> img;

		Mat img_out, img_out_out;

		
		GaussianBlur(img, img_out, 3, 0,0, BORDER_DEFAULT );
		cvtColor(img_out, img_out_out, CV_BGR2HSV);

		namedWindow("win", WINDOW_NORMAL);
		imshow("win", img_out_out);
		waitKey(5);
		//return 0;
	}
}
