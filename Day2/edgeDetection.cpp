#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

Mat img ;
int rows;
int cols;

int **kernel_matrix;

void dilation(int i, int j, Mat img_e, Mat img_d)
{
	int p, q, sum = 0;

    for(p = i - 1; p <= i+1; p++)
        for(q = j - 1; q <= j + 1; q++)
        {
            if( p >= 0 && p < rows && q >= 0 && q < cols)
            {
            	sum += img_e.at<uchar>(p , q);
            }
        }

    if(sum > 0)
    	img_d.at<uchar>(i , j) = 255;
}

void erosion(int i, int j, Mat img_e, Mat img_d)
{
	int p, q, sum = 0, count = 0;

    for(p = i - 1; p <= i+1; p++)
        for(q = j - 1; q <= j + 1; q++)
        {
            if( p >= 0 && p < rows && q >= 0 && q < cols)
            {
            	sum += img_e.at<uchar>(p , q);
            	count++;
            }
        }

    if((int)(sum / count) < 250)
    	img_d.at<uchar>(i , j) = 0;
}

int gaussianBlur(int i, int j, Mat img)
{
    int p, q, sum = 0;

    for(p = i - 1; p <= i+1; p++)
        for(q = j - 1; q <= j + 1; q++)
        {
            if( p >= 0 && p < rows && q >= 0 && q < cols)
            {

                if(p == i && q == j)
                    sum += ( img.at<uchar>(p , q) ) / 4;

                else if( (p == i - 1 && ( q == j - 1 ||  q == j + 1) ) || (p == i + 1 && ( q == j - 1 || q == j + 1)))
                    sum += ( img.at<uchar>(p , q) ) / 16;

                else
                    sum += ( img.at<uchar>(p , q) ) / 8;
            }
        }

    return sum;
}

int gx_squared(int i, int j, Mat img_grayscale)
{
	int sum = 0;

	for(int p = i - 1; p < i + 1; p++)
	{
		for(int q = j - 1; q < j + 1; q++)
		{
			if(q == j - 1)
			{	
				if(p == i)
					sum += (-2) * img_grayscale.at<uchar>(p , q);
				else
					sum += (-1) * img_grayscale.at<uchar>(p , q);
			}

			else if( q == j + 1)
			{
				if(p == i)
					sum += 2 * img_grayscale.at<uchar>(p , q);
				else
					sum += img_grayscale.at<uchar>(p , q);
			}

			else
				continue;	
		}
			
	}

	return pow(sum , 2) / 8;
}

int gy_squared(int i, int j, Mat img_grayscale)
{
	int sum = 0;

	for(int p = j - 1; p < j + 1; p++)
	{
		for(int q = i - 1; q < i + 1; q++)
		{
			if(q == i - 1)
			{	
				if(p == j)
					sum += (-2) * img_grayscale.at<uchar>(q , p);
				else
					sum += (-1) * img_grayscale.at<uchar>(q , p);
			}

			else if( q == i + 1)
			{
				if(p == j)
					sum += 2 * img_grayscale.at<uchar>(q , p);
				else
					sum += img_grayscale.at<uchar>(q , p);
			}

			else
				continue;	
		}
			
	}

	return pow(sum , 2) / 8;

}

void updateFun(int threshold, void *)
{
	//cout << "yes\n";
    //edgeDetection
    Mat edgedImage(rows - 2, cols - 2, CV_8UC1, Scalar(0));

    //initializing
    for(int i = 0; i < rows - 2; i++)
    	for(int j = 0; j < cols - 2; j++)
    		edgedImage.at<uchar>(i , j) = kernel_matrix[i][j];
    //cout << "yes\n";
    for(int i = 0; i < rows - 2; i++)
    	for(int j = 0; j < cols - 2; j++)
    	{
    		if(kernel_matrix[i][j] > threshold)
    		{
    			edgedImage.at<uchar>(i , j) = 0;
    		}

    		else
    			edgedImage.at<uchar>(i , j) = 255;
    	}
    

    //cout << "yes\n";
    Mat dilatedImage(rows - 2, cols - 2, CV_8UC1, Scalar(0));
    for(int i = 0; i < rows - 2; i++)
    	for(int j = 0; j < cols - 2; j++)
    		dilatedImage.at<uchar>(i , j) = edgedImage.at<uchar>(i , j);

    for(int i = 0; i < rows - 2; i++)
    	for(int j = 0; j < cols - 2; j++)
    		dilation(i , j, edgedImage, dilatedImage);
    

    //cout << "yes\n";
    Mat erodedImage(rows - 2, cols - 2, CV_8UC1, Scalar(0));
    for(int i = 0; i < rows - 2; i++)
    	for(int j = 0; j < cols - 2; j++)
    		erodedImage.at<uchar>(i , j) = dilatedImage.at<uchar>(i , j);
    //cout << "yes\n";
    for(int i = 0; i < rows - 2; i++)
    	for(int j = 0; j < cols - 2; j++)
    		erosion(i , j, dilatedImage, erodedImage);

    //cout << "yes\n";
    namedWindow("win_dil", WINDOW_NORMAL);
    namedWindow("win_ero", WINDOW_NORMAL);
    imshow("win", edgedImage);
    imshow("win_dil", dilatedImage);
    imshow("win_ero", erodedImage);
}

int main()
{
	int threshold = 0;

	img = imread("rubik.jpg", 1);
	rows = img.rows;
	cols = img.cols;

	cout << "yes\n";

	//conversion to grayscale
	Mat img_grayscale(rows, cols, CV_8UC1, Scalar(0));

    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
        {
            img_grayscale.at<uchar>(i, j) = (0.21)*img.at<Vec3b>(i,j)[2] + (0.72)*img.at<Vec3b>(i,j)[1] + (0.07)*img.at<Vec3b>(i,j)[0];
        }
    }

    //gaussianBlur
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
        {
            img_grayscale.at<uchar>(i , j) = gaussianBlur(i, j ,img_grayscale);
        }
	
    //calculating kernel matrix
    //allocating memory
    kernel_matrix = (int **)malloc(sizeof(int *) * (rows - 2));
    for(int i = 0; i < rows - 2; i++)
    {
    	kernel_matrix[i] = (int *)malloc(sizeof(int) * (cols - 2));
    }

    //cout << "yes\n";

    for(int i = 1; i < rows - 1; i++)
    	for(int j = 1; j < cols - 1; j++)
    	{
    		int kernel_value = sqrt(gx_squared(i , j , img_grayscale) + gy_squared(i , j , img_grayscale));
    		//cout << "kvalue = " << kernel_value << "\n"; 
    		kernel_matrix[i - 1][j - 1] = kernel_value;
    	}

    //cout << "yes\n";

    Mat kmImage(rows - 2, cols - 2, CV_8UC1, Scalar(0));
    for(int i = 0; i < rows - 2; i++)
    	for(int j = 0; j < cols - 2; j++)
    		kmImage.at<uchar>(i , j) = kernel_matrix[i][j];
	
    namedWindow("win", WINDOW_NORMAL);
    namedWindow("win_gray", WINDOW_NORMAL);
    namedWindow("win_km", WINDOW_NORMAL);
    imshow("win_km",kmImage);
    imshow("win_gray", img_grayscale);
    createTrackbar("trackbar", "win", &threshold, 1000, updateFun);
    waitKey(0);
    return 0;

}