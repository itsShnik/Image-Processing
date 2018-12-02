#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

int main()
{
	int boxSize = 75;
	int imageSize = 8 * boxSize;

	Mat chessboard(imageSize, imageSize, CV_8UC1, Scalar(0));

	for(int i = 0; i < imageSize; i ++)
		for(int j = 0; j < imageSize; j ++)
		{
			if((i / 75) % 2 == 0)
			{
				if((j / 75) % 2 == 0)
					chessboard.at<uchar>(i , j) = 0;
				else
					chessboard.at<uchar>(i , j) = 255;
			}

			else
			{
				if((j / 75) % 2 == 0)
					chessboard.at<uchar>(i , j) = 255;
				else
					chessboard.at<uchar>(i , j) = 0;
			}			 
		}

	namedWindow("win", WINDOW_NORMAL);
	imshow("win", chessboard);
	waitKey(0);
	return 0;
}