#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;

int main ()
{
    Mat img = imread("Lena.jpg", 1) ;
    namedWindow("win", WINDOW_NORMAL);

    int rows = img.rows;
    int cols = img.cols;

    Mat img_temp(rows, cols, CV_8UC3, Scalar(0));

    int mid = cols/2;

    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<mid; j++)
        {
            img_temp.at<Vec3b>(i,j) = img.at<Vec3b>(i, j);
        }
        for (int j=mid; j<cols; j++)
        {
            img.at<Vec3b>(i,cols-j-1) = img.at<Vec3b>(i, j);
        }
        for (int j=mid-1; j>=0; j--)
        {
            img.at<Vec3b>(i, cols-j) = img_temp.at<Vec3b>(i, j);
        }
    }

    imshow("win", img);
    waitKey(0);

    return 0;
}
