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

void BFS(int i, int j, Mat bin_img)
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
				
				if(a >= 0 && a < rows && b >= 0 && b < cols && vis[a][b] == 0 && img.at<uchar>(a , b) < tr)
				{
					
					vis[a][b] = 1;
					bin_img.at<uchar>(a, b) = 0;
					p1.x = a;
					p1.y = b;
					mq.push(p1);
				}
			}
	}
}

int main()
{
	VideoCapture cap(0);

	//img = imread("dfs_path.jpg", 0);
	while(1)
	{
		cap >> img;
		rows = img.rows;
		cols = img.cols;

		tr = 125;

		int blob_count = 0;

		Mat bin_img(rows, cols, CV_8UC1, Scalar(255));

		//int vis[rows][cols];
		
		vis = (int  **)malloc(sizeof(int*) * rows);
		for(int i = 0; i < rows; i++)
			vis[i] = (int *)malloc(sizeof(int) * cols);

		

		for(int i = 0 ; i < rows; i++)
			for(int j = 0; j < cols; j++)
			{
				vis[i][j] = 0;
			}

		
		

		for(int i = 0 ; i < rows; i++)
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

		
		//cout << "blob_count = " << blob_count << endl;

		namedWindow("win", WINDOW_NORMAL);
		namedWindow("win_bin", WINDOW_NORMAL);
		imshow("win", img);
		imshow("win_bin", bin_img);

	}
	
	waitKey(0);
	return 0;
}