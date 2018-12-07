#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(0);

	Mat img;

	while(1)
	{
		cap >> img;

		Mat img_out;

		Canny(img, img_out, 50, 130, 3, false);

		namedWindow("win", WINDOW_NORMAL);
		imshow("win", img_out);
		waitKey(5);
		//return 0;
	}
	
}