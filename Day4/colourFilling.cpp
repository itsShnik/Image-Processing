#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
#include <cmath>
#include <queue>

using namespace cv;
using namespace std;

typedef struct _point
{
	int x;
	int y;
}point;

Mat img;
int rows;
int cols;
int **vis;
int tr;

void BFS(int i, int j)
{	
	queue < point > mq;

	point p , p1;
	p.x = i;
	p.y = j;

	mq.push(p);
	
	while(!mq.empty())
	{
		
		p = mq.front();
		mq.pop();
		
		for(int a = p.x - 1; a <= p.x + 1; a++)
			for(int b = p.y - 1; b <= p.y + 1; b++)
			{	
				
				if(a >= 0 && a < rows && b >= 0 && b < cols && vis[a][b] == 0 && img.at<Vec3b>(a , b)[2] < tr)
				{
					
					vis[a][b] = 1;
					img.at<Vec3b>(a, b)[2] = 255 ;
					p1.x = a;
					p1.y = b;
					mq.push(p1);
				}
			}
	}
}

void onMouse(int event, int y, int x, int flag, void *)
{

	tr = 125;

	//int blob_count = 0;

	//Mat RGB_img(rows, cols, CV_8UC3, Scalar(0));

	//int vis[rows][cols];
	
	vis = (int  **)malloc(sizeof(int*) * rows);
	for(int i = 0; i < rows; i++)
		vis[i] = (int *)malloc(sizeof(int) * cols);

	

	for(int i = 0 ; i < rows; i++)
		for(int j = 0; j < cols; j++)
		{
			vis[i][j] = 0;
		}

	
	if(vis[x][y] == 0 && event == 1)
		BFS(x, y);

	/*for(int i = 0 ; i < rows; i++)
		for(int j = 0; j < cols; j++)
		{
			if(vis[i][j] == 0)
			{
				vis[i][j] = 1;
				if(img.at<uchar>(i , j) < tr)
				{	
					
					bin_img.at<uchar>(i , j) = 0;
					BFS(i , j, bin_img);
					blob_count++;
				}
			}
		}
	*/
	
	//cout << "blob_count = " << blob_count << endl;

	//namedWindow("win", WINDOW_NORMAL);
	//namedWindow("win_bin", WINDOW_NORMAL);
	imshow("win", img);
	//imshow("win_bin", RGB_img);
	//waitKey(10000);
	
}

int main()
{
	img = imread("dfs_path.jpg", 1);
	rows = img.rows;
	cols = img.cols;

	namedWindow("win", WINDOW_NORMAL);
	setMouseCallback("win", onMouse);
	waitKey(0);
	return 0;
}
