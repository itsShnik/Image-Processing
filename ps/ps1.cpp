#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;


int main()
{
	//VideoCapture cap(0);

	//Mat img;

	//while(1)
	//{
		//cap >> img;
		Mat img = imread("1.jpg", 1);
		int rows = img.rows;
		int cols = img.cols;

		int Rh = 255, Bh = 240, Gh = 240, Rl = 240, Bl = 97, Gl = 170;

		//image segmentation
		Mat imgnew(rows, cols, CV_8UC1, Scalar(0));

	    for (int i=0; i<rows; i++)
	    {
	        for (int j=0; j<cols; j++)
	        {
	            imgnew.at<uchar>(i,j) = 255;
	        }
	    }

	    for (int i=0; i<rows; i++)
	    {
	        for (int j=0; j<cols; j++)
	        {
	            if ((img.at<Vec3b>(i, j)[0] >= Bl) && (img.at<Vec3b>(i, j)[0] <= Bh) && (img.at<Vec3b>(i, j)[1] >= Gl) && (img.at<Vec3b>(i, j)[1] <= Gh) && (img.at<Vec3b>(i, j)[2] >= Rl) && (img.at<Vec3b>(i, j)[2] <= Rh))
	            {
	                imgnew.at<uchar>(i, j) = 0;
	            }
	            else
	                imgnew.at<uchar>(i , j) = 255;
	        }
    	}



    	namedWindow("win", WINDOW_NORMAL);
    	imshow("win", imgnew);
    	waitKey(0);
	//}
}