#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace cv;

int R;
int G;
int B;

int rows;
int cols;

Mat img;

void update_funR(int t, void* )
{
    //printf("rows = %d\n",rows);
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            //printf("hello red, t = %d\n", t);
            if(img.at<Vec3b>(i,j)[2] < t)
                img.at<Vec3b>(i,j)[2] = 0;

            else
                img.at<Vec3b>(i,j)[2] = 255;
        }
    }
    //printf("rows, loop out = %d\n",rows);

    imshow("win", img);
}

void update_funG(int t, void* )
{

    //img = imread("Lena.jpg", 1);
    //printf("rows = %d\n",rows);


    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(img.at<Vec3b>(i,j)[1] < t)
                img.at<Vec3b>(i,j)[1] = 0;

            else
                img.at<Vec3b>(i,j)[1] = 255;
        }
    }
    //printf("rows = %d\n",rows);

    imshow("win", img);
}


void update_funB(int t, void* )
{

    //img = imread("Lena.jpg", 1);

    //printf("rows = %d\n",rows);

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(img.at<Vec3b>(i,j)[0] < t)
                img.at<Vec3b>(i,j)[0] = 0;

            else
                img.at<Vec3b>(i,j)[0] = 255;
        }
    }
    //printf("rows = %d\n",rows);

    imshow("win", img);
}

int main()
{
    img = imread("Lena.jpg", 1);
    rows = img.rows;
    cols = img.cols;

    //printf("rows = %d\n",rows);

    R = G = B = 0;

    namedWindow("win", WINDOW_NORMAL);
    createTrackbar("tnR", "win", &R, 255, update_funR);
    createTrackbar("tnG", "win", &G, 255, update_funG);
    createTrackbar("tnB", "win", &B, 255, update_funB);
    waitKey(0);

    return 0;

}
