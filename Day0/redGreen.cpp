#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

int main()
{
	Mat img(1200, 1200, CV_8UC3, Scalar(0));

	for(int i = 0; i < img.rows; i++)
		for(int j = 0; j < img.cols; j++)
		{
			if(i < j)
			{
				img.at<Vec3b>(i , j)[2] = 255;
				img.at<Vec3b>(i , j)[1] = 0;
				img.at<Vec3b>(i , j)[0] = 0;
			}

			else
			{
				img.at<Vec3b>(i , j)[2] = 0;
				img.at<Vec3b>(i , j)[1] = 255;
				img.at<Vec3b>(i , j)[0] = 0;
			}
		}

	namedWindow("win", WINDOW_NORMAL);
	imshow("win", img);
	waitKey(0);
}