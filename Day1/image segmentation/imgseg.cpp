#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace cv;

int Rh;
int Rl;
int Gh;
int Gl;
int Bh;
int Bl;

int rows;
int cols;

Mat img;
Mat imgcpy;

void update_funRh(int t, void* )
{
    //printf("rows = %d\n",rows);
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            //printf("hello red, t = %d\n", t);
            if(img.at<Vec3b>(i,j)[2] > t)
                imgcpy.at<Vec3b>(i,j)[2] = 0;

            // else
                // imgcpy.at<Vec3b>(i,j)[2] = img.at<Vec3b>(i, j);
        }
    }
    //printf("rows, loop out = %d\n",rows);

    imshow("win", imgcpy);
}

void update_funRl(int t, void* )
{
    //printf("rows = %d\n",rows);
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            //printf("hello red, t = %d\n", t);
            if(img.at<Vec3b>(i,j)[2] < t)
                imgcpy.at<Vec3b>(i,j)[2] = 0;

            // else
                // imgcpy.at<Vec3b>(i,j)[2] = 255;
        }
    }
    //printf("rows, loop out = %d\n",rows);

    imshow("win", imgcpy);
}

void update_funBh(int t, void* )
{
    //printf("rows = %d\n",rows);
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            //printf("hello red, t = %d\n", t);
            if(img.at<Vec3b>(i,j)[2] > t)
                imgcpy.at<Vec3b>(i,j)[2] = 0;

            // else
                // imgcpy.at<Vec3b>(i,j)[2] = 255;
        }
    }
    //printf("rows, loop out = %d\n",rows);

    imshow("win", imgcpy);
}

void update_funBl(int t, void* )
{
    //printf("rows = %d\n",rows);
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            //printf("hello red, t = %d\n", t);
            if(img.at<Vec3b>(i,j)[2] < t)
                imgcpy.at<Vec3b>(i,j)[2] = 0;

            // else
                // imgcpy.at<Vec3b>(i,j)[2] = 255;
        }
    }
    //printf("rows, loop out = %d\n",rows);

    imshow("win", imgcpy);
}

void update_funGh(int t, void* )
{
    //printf("rows = %d\n",rows);
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            //printf("hello red, t = %d\n", t);
            if(img.at<Vec3b>(i,j)[2] > t)
                imgcpy.at<Vec3b>(i,j)[2] = 0;

            // else
                // imgcpy.at<Vec3b>(i,j)[2] = 255;
        }
    }
    //printf("rows, loop out = %d\n",rows);

    imshow("win", imgcpy);
}

void update_funGl(int t, void* )
{
    //printf("rows = %d\n",rows);
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            //printf("hello red, t = %d\n", t);
            if(img.at<Vec3b>(i,j)[2] < t)
                imgcpy.at<Vec3b>(i,j)[2] = 0;

            // else
                // imgcpy.at<Vec3b>(i,j)[2] = 255;
        }
    }
    //printf("rows, loop out = %d\n",rows);

    imshow("win", imgcpy);
}

int main()
{
    //printf("rows = %d\n",rows);
    img = imread("FruitBasket.jpg", 1);
    rows = img.rows;
    cols = img.cols;

    Mat imgcpy(rows, cols, CV_8UC3, Scalar(0));


    for (int i=0; i<rows; i++)
    {
        //printf("outer loop rows = %d\n",rows);
        for (int j=0; j<cols; j++)
        {
            //printf("inner loop rows = %d\n",rows);
            imgcpy.at<Vec3b>(i, j) = img.at<Vec3b>(i, j);
        }
    }

    //printf("rows = %d\n",rows);

    Rh = Gh = Bh = Rl = Gl = Bl = 0;

    namedWindow("win", WINDOW_NORMAL);
    createTrackbar("tnRh", "win", &Rh, 255, update_funRh);
    createTrackbar("tnGh", "win", &Gh, 255, update_funGh);
    createTrackbar("tnBh", "win", &Bh, 255, update_funBh);
    createTrackbar("tnRl", "win", &Rl, 255, update_funRl);
    createTrackbar("tnGl", "win", &Gl, 255, update_funGl);
    createTrackbar("tnBl", "win", &Bl, 255, update_funBl);
    waitKey(0);

    return 0;

}
