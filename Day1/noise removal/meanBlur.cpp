#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace cv;

Mat img;
int rows;
int cols;

int kernel(int i, int j, Mat img)
{
    int sum = 0;
    int count = 0;

    for(int p = i - 1; p <= i + 1; p++)
        for(int q = j - 1; q <= j +1; q++)
        {
            if(p >= 0 && p < rows && q >= 0 && q < cols)
            {
                sum += img.at<uchar>(p , q);
                count++;
            }
        }
    return sum/count;
}

int main()
{
    img = imread("NoisyLana.jpg", 1);

    rows = img.rows;
    cols = img.cols;

    Mat img_gauss(rows, cols, CV_8UC1, Scalar(0));

    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
        {
            img_gauss.at<uchar>(i, j) = (0.21)*img.at<Vec3b>(i,j)[2] + (0.72)*img.at<Vec3b>(i,j)[1] + (0.07)*img.at<Vec3b>(i,j)[0];
        }
    }

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            img_gauss.at<uchar>(i , j) = kernel(i , j, img_gauss);
        }
    }

    namedWindow("win", WINDOW_NORMAL);
    namedWindow("win_edited", WINDOW_NORMAL);
    imshow("win_edited", img_gauss);
    imshow("win", img);
    waitKey(0);
    return 0;
}
