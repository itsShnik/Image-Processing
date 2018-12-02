#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace cv;

Mat img_gauss;
//namedWindow("win_gauss", WINDOW_NORMAL);

void update_fun(int t, void* )
{

    Mat img = imread("Lena.jpg", 1);

    int rows = img.rows;
    int cols = img.cols;


    Mat img_gauss(rows, cols, CV_8UC1, Scalar(0));

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            img_gauss.at<uchar>(i , j) = (0.07) * img.at<Vec3b>(i , j)[0] + (0.72) * img.at<Vec3b>(i , j)[1] + (0.21) * img.at<Vec3b>(i , j)[2];

            if(img_gauss.at<uchar>(i,j) < t)
                img_gauss.at<uchar>(i,j) = 0;

            else
                img_gauss.at<uchar>(i,j) = 255;
        }
    }


    //printf("rows = %d\n",rows);

    imshow("win_gauss", img_gauss);
}

int main()
{
    int threshold = 0;

    namedWindow("win_gauss", WINDOW_NORMAL);
    createTrackbar("tn", "win_gauss", &threshold, 255, update_fun);
    waitKey(0);

    return 0;

}
