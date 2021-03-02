#include <opencv2/opencv.hpp>
#include <iostream>
#include "opencv2\core\fast_math.hpp"
#include "opencv2/core.hpp"
#include <cstring>
#include <string>
#include <cstringt.h>
#include <opencv2/highgui/highgui_c.h>
#include<vector>
#include <fstream>
using namespace std;
using namespace cv;
/*
1、用C语言完成一副图像上分别叠加椒盐噪声、高斯噪声，噪声在图像上叠加比例不超过20%，
噪声依靠概率论所学方法产生，不可直接调用OpenCV相关函数。
图像内容为作业完成人的自拍（可生活、可证件）。
2、用C语言完成对一个任意n阶方阵求逆矩阵的函数，并将函数的实现机理写成报告，随代码一同提交。
上交时间：2019年12月21日00：00之前
方式：邮件发送助教-唐兆家(171287719)，压缩包形式，邮件名称：学号-姓名-图像处理第三次作业。
得分规则：提交的代码要有示例，可以简单编译验证。 作业雷同，后交者不得分。报告无排版者不得分。
*/
/*
思路：
1：读入BMP图像
2：读入图片的每个像素点
3：对图片的像素点进行操作
*/

int main(int argc, char**argv)
{
	//读入图片//task1:读入图片
	string impath = "D://88.bmp";
	Mat src = imread(impath);
	namedWindow("椒盐叠加图像", 0);//创建窗口 
	namedWindow("原图", 0);//创建窗口
	cvResizeWindow("椒盐叠加图像", 500, 500); //创建一个500*500大小的窗口
	cvResizeWindow("原图", 500, 500); //创建一个500*500大小的窗口
	imshow("原图", src);//在创建的窗口中显示原图 
	//判断是否正确读入图片
	if (src.empty())
	{
		cout << "could not load image..." << endl;
		return false;
	}
	//生成一个用于叠加噪声的随机数组//task2:生成随机数组
	int **RandomArray = new int*[src.rows + 1];
	for (int i = 1; i < src.rows + 1; ++i)
		RandomArray[i] = new int[src.cols + 1];
	for (int i = 1; i <= src.rows; i++) {
		for (int j = 1; j <= src.cols; j++) {
			RandomArray[i][j] = (rand() % (255 - 0 + 1)) + 0;
			//要取得[a,b)的随机整数，使用(rand() % (b-a))+ a;   			
			//要取得[a,b]的随机整数，使用(rand() % (b-a+1))+ a;   			
			//要取得(a,b]的随机整数，使用(rand() % (b-a))+ a + 1;   		
		}
	}
	//计算要添加噪声的数据范围小于20%//task3:计算随机噪声叠加范围
	int down1 = 0, up1 = 255 * 1 / 10;//0-0.1
	int down2 = 255 * 9 / 10, up2 = 255;//0.9-1

	//对图像进行概率叠加　　
	for (int i = 1; i < src.rows; i++)
	{
		for (int j = 1; j < src.cols; j++)
		{
			if (RandomArray[i][j]<up1&&RandomArray[i][j]>down1)
			{
				src.at<Vec3b>(i, j)[0] = 0;
				src.at<Vec3b>(i, j)[1] = 0;
				src.at<Vec3b>(i, j)[2] = 0;
			}
			else if (RandomArray[i][j]<up2&&RandomArray[i][j]>down2)
			{
				for (int p = 0; p < 3; p++)
					src.at<Vec3b>(i, j)[p] = 255;
			}
		}
	}
	imshow("椒盐叠加图像", src);//在创建的窗口中显示图片
	waitKey(0);
	return 0;
}

