#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"
#include<math.h>
using namespace std;
using namespace cv;
Mat img = imread("./lenna.jpg" ,1);
int p=sqrt(img.rows*img.rows+img.cols*img.cols);
void callback(int low, void*)
{
	Mat img2(2*p,2*p,CV_8UC3,Scalar(0,0,0));
	int ic,jc,i,j,x1,y1;
	ic=img2.rows/2;
	jc=img2.cols/2;

		/* code */
	for(i=0;i<img.rows;i++)
	{
		for(j=0;j<img.cols;j++)
		{
			x1=((i)*cos(low*M_PI/180.0)-(j)*sin(low*M_PI/180.0));
			y1=((i)*sin(low*M_PI/180.0)+(j)*cos(low*M_PI/180.0));

			x1 = x1 + ic;
			y1 = y1 + jc;

			img2.at<Vec3b>(x1,y1)[0]=img.at<Vec3b>(i,j)[0];
			img2.at<Vec3b>(x1,y1)[1]=img.at<Vec3b>(i,j)[1];
			img2.at<Vec3b>(x1,y1)[2]=img.at<Vec3b>(i,j)[2];
		}
	}
	imshow("win",img2);

}

int main()
{
	imshow("test", img);
	int var=0;
	namedWindow("win",WINDOW_NORMAL);
	createTrackbar("greyscale","win",&var,360,callback);
waitKey(0);
return 0;
}