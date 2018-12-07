#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
#include <cmath>
#include <queue>

using namespace cv;
using namespace std;


int main()
{
  	Mat img = imread("66.jpg", 1);
  	int rows = img.rows;
  	cout << rows << endl;

  	Mat dst, cdst;

  	Canny(img, dst, 50, 130, 3);
  	cvtColor(dst, cdst, CV_GRAY2BGR);

  	vector<Vec4i> lines;
  	HoughLinesP(dst, lines, 1, CV_PI/180, 50, 100, 100 );

    cout << lines.size() << endl;
  	
  	for( size_t i = 0; i < lines.size(); i++ )
  	{
    	Vec4i l = lines[i];
    	line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
  	}

    namedWindow("source", WINDOW_NORMAL);
    namedWindow("detected lines", WINDOW_NORMAL);
    namedWindow("dst", WINDOW_NORMAL);
  	imshow("source", img);
 	  imshow("detected lines", cdst);
    imshow("dst", dst);
 	  waitKey(0);
}