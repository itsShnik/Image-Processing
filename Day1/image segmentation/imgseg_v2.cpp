#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace cv;

// globally define the image
Mat img;

// globally define all the parameters of the Trackbar
int Rh;
int Rl;
int Gh;
int Gl;
int Bh;
int Bl;

int rows;
int cols;
/*
*
*/
void update_fun(int t, void* )
{
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
            if ((img.at<Vec3b>(i, j)[0] > Bl) && (img.at<Vec3b>(i, j)[0] < Bh) && (img.at<Vec3b>(i, j)[1] > Gl) && (img.at<Vec3b>(i, j)[1] < Gh) && (img.at<Vec3b>(i, j)[2] > Rl) && (img.at<Vec3b>(i, j)[2] < Rh))
            {
                imgnew.at<uchar>(i, j) = 0;
            }
            else
                imgnew.at<uchar>(i , j) = 255;
        }
    }

    imshow("win", imgnew);
}

int main()
{
    img = imread("FruitBasket.jpg", 1);
    rows = img.rows;
    cols = img.cols;

    namedWindow("win", WINDOW_NORMAL);
    createTrackbar("tnRh", "win", &Rh, 255, update_fun);
    createTrackbar("tnGh", "win", &Gh, 255, update_fun);
    createTrackbar("tnBh", "win", &Bh, 255, update_fun);
    createTrackbar("tnRl", "win", &Rl, 255, update_fun);
    createTrackbar("tnGl", "win", &Gl, 255, update_fun);
    createTrackbar("tnBl", "win", &Bl, 255, update_fun);

    waitKey(0);

    return 0;
}
