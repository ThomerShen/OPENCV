// 滑动条的创建与使用.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

#define WINDOW_NAME "【线性混合示例】"
//定义全局变量
const int g_nMaxAlphaValue = 100;
int g_nAlphaValueSlider;
double g_dAlphaValue;
double g_dBetaValue;

Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

//响应滑动条的回调函数
void on_Tracbar(int, void*)
{
	g_dAlphaValue = (double)g_nAlphaValueSlider / g_nMaxAlphaValue;
	g_dBetaValue = 1.0 - g_dAlphaValue;
	//线性混合
	addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);
	imshow(WINDOW_NAME, g_dstImage);
}

//主函数
int main(int argc, char** argv)
{
	g_srcImage1 = imread("1.jpg");
	g_srcImage2 = imread("2.jpg");
	if (!g_srcImage1.data) {
		cout << "读取第一幅图片错误，请确认目录下是否有imread指定的图片存在！\n" << endl;
		return -1;
	}
	if (!g_srcImage2.data) {
		cout << "读取第二幅图片错误，请确认目录下是否有imread指定的图片存在！\n" << endl;
		return -1;
	}

	g_nAlphaValueSlider = 70;//设置滑动条的初始值
	namedWindow(WINDOW_NAME,1);//新窗口

	char TracbarName[50];
	sprintf_s(TracbarName, "透明值 %d", g_nMaxAlphaValue);
	//在新建的窗口中创建一个滑动条控件
	createTrackbar(TracbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Tracbar);
	on_Tracbar(g_nAlphaValueSlider, 0);
	waitKey(0);

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
