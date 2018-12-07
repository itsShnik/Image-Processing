/*
Hough's transform:
tasks to do:
>read an image
>convert to grayscale
>edge detection using canny
>for each r and theta, check for each point if that satisfies the value of r and theta
>in the intensity image for r and theta, increase ther count
>loop through the image and store the values of r and theta for which count is greater than a threshold
>for those values of r and theta iterate through all the points and make their density on an output image equal to 255
*/
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
#include <cmath>
#include <queue>

using namespace cv;
using namespace std;

typedef struct _line
{
	int r;
	int theta;
}lined;

int main()
{
		Mat img = imread("pentagon.png", 0);
		int rows = img.rows;
    	int cols = img.cols;

		Mat img_edged, img_out;

		int count = 0;

		lined arr[30];

		int r = sqrt(pow(rows, 2) + pow(cols, 2)) , theta = 360;
		Mat img_int(r, theta, CV_8UC1, Scalar(0));
		for(int rr = 0; rr < r; rr++)
			for(int thetar = 0; thetar < 360; thetar++)
			{
				img_int.at<uchar>(rr, thetar) = 0;
			}

		Canny(img, img_edged, 50, 130, 3, false);

		namedWindow("wind", WINDOW_NORMAL);
		imshow("wind", img_edged);

		for(int rr = 0; rr < r; rr += 5)
			for(int thetar = 0; thetar < 360; thetar += 10)
			{	
				cout << "r, theta = " << rr << thetar << endl;

				for(int x = 0; x < rows; x++)
					for(int y = 0; y < cols; y++)
					{
						//cout << "hello" << endl;
						if((int)(x * cos(thetar * CV_PI / 180) + y * sin(thetar * CV_PI / 180) - rr) == 0 && img_edged.at<uchar>(x, y) > 120)
						{
							cout << "hello" << endl;
							img_int.at<uchar>(rr, thetar) += 20;
							if(img_int.at<uchar>(rr, thetar) > 255)
								img_int.at<uchar>(rr, thetar)  = 255;
						}
					}
			}


		/*for(int rr = 0; rr < r; rr++)
			for(int thetar = 0; thetar < 360; thetar++)
			{
				if(img_int.at<uchar>(rr, thetar) > threshold)
				{
					arr[count].r = rr;
					arr[count].thetar = thetar;
					count++;			
				}
			}	
		*/

		namedWindow("win", WINDOW_AUTOSIZE);
		imshow("win", img_int);
		waitKey(0);
}