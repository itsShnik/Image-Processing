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

void DFSvisit(int i, int j, Mat bin_img)
{	

	point p , p1;
	p.x = i;
	p.y = j;

	for(int a = p.x - 1; a <= p.x + 1; a++)
			for(int b = p.y - 1; b <= p.y + 1; b++)
			{	
				
				if(a >= 0 && a < rows && b >= 0 && b < cols && vis[a][b] == 0 && img.at<uchar>(a , b) < tr)
				{
					
					vis[a][b] = 1;
					bin_img.at<uchar>(a, b) = 0;
					DFSvisit(a , b , bin_img);
				}
			}
	
}