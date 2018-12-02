#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int findMax(int arr[], int n)
{
	int max = -1;
	for(int i = 0; i < n; i++)
	{
		if(arr[i] > max)
			max = arr[i];
	}

	return max;
}

int main()
{
	Mat img = imread("constant.jpg", 1);
	int rows = img.rows;
    int cols = img.cols;

    Mat img_greyscale(rows, cols, CV_8UC1, Scalar(0));
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
        {
            img_greyscale.at<uchar>(i, j) = (0.21)*img.at<Vec3b>(i,j)[2] + (0.72)*img.at<Vec3b>(i,j)[1] + (0.07)*img.at<Vec3b>(i,j)[0];
        }
    }

    //creating an array to represent the no. of pixels with a particular intensity
    int arr[256] = {0};

    for(int i = 0; i < rows; i++)
    	for(int j = 0; j < cols; j++)
    	{
    		arr[ img.at<uchar>(i , j) ]++;
    	}

    int max = findMax(arr, 256);
    cout << "max = " << max << "\n";

    //create the histogram image
    Mat histogram(max, 256, CV_8UC1, Scalar(0));

    for(int i = 0; i < max; i++)
    	for(int j = 0; j < 256; j++)
    	{
    		histogram.at<uchar>(i , j) = 255;
    	}
	
	for(int j = 0; j < 256; j++)
	{
		

		for(int i = max - arr[j]; i < max; i++)
		{
			//cout << "hello\n";
			histogram.at<uchar>(i , j) = 0;
		}
	} 

	cout << "hello\n";

	namedWindow("win", WINDOW_NORMAL);
    namedWindow("win_histogram", WINDOW_NORMAL);
    imshow("win", img_greyscale);
    imshow("win_histogram", histogram);
    waitKey(0);
    return 0;
}