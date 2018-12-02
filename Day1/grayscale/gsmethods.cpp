#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat img = imread("Lena.jpg", 1);
    namedWindow("win_avg",WINDOW_NORMAL);
    // namedWindow("maxmin_win",WINDOW_NORMAL);
    namedWindow("win_gauss",WINDOW_NORMAL);

    int rows = img.rows;
    int cols = img.cols;

    Mat img_avg(rows, cols, CV_8UC1, Scalar(0));
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
        {
            img_avg.at<uchar>(i, j) = (img.at<Vec3b>(i,j)[0]+img.at<Vec3b>(i,j)[1]+img.at<Vec3b>(i,j)[2])/3;
        }
    }

    /*
    Mat img_maxmin(rows, cols, CV_8UC1, Scalar(0));
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
        {
            img_maxmin.at<uchar>(i, j) = (Max(img.at<Vec3b>(i,j)[0], img.at<Vec3b>(i,j)[1], img.at<Vec3b>(i,j)[2]) + Min(img.at<Vec3b>(i,j)[0], img.at<Vec3b>(i,j)[1], img.at<Vec3b>(i,j)[2]))/2;
        }
    }*/

    Mat img_gauss(rows, cols, CV_8UC1, Scalar(0));
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
        {
            img_gauss.at<uchar>(i, j) = (0.21)*img.at<Vec3b>(i,j)[2] + (0.72)*img.at<Vec3b>(i,j)[1] + (0.07)*img.at<Vec3b>(i,j)[0];
        }
    }

    imshow("win_avg", img_avg);
    // imshow("win_maxmin", img_maxmin);
    imshow("win_gauss", img_gauss);
    waitKey(0);

    return 0;
}
