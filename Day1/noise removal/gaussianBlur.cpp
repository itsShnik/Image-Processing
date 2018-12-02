#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace cv;

int rows;
int cols;

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

int main()
{
    Mat img = imread("NoisyLana.jpg", 1);
    rows = img.rows;
    cols = img.cols;

    Mat imgcpy(rows, cols, CV_8UC1, Scalar(0));

    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
        {
            imgcpy.at<uchar>(i , j) = (0.21)*img.at<Vec3b>(i,j)[2] + (0.72)*img.at<Vec3b>(i,j)[1] + (0.07)*img.at<Vec3b>(i,j)[0];

        }

    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
        {
            imgcpy.at<uchar>(i , j) = gaussianBlur(i, j ,imgcpy);
        }

    namedWindow("win", WINDOW_NORMAL);
    namedWindow("win_edited", WINDOW_NORMAL);
    imshow("win", img);
    imshow("win_edited", imgcpy);
    waitKey(0);

    return 0;
}
