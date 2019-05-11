// 鼠标操作.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

#define WINDOW_NAME "【程序窗口】"
//定义全局变量
Rect g_rectangle;
bool g_bDrawingBox = false;
RNG g_rng(12345);

//自定义的矩形绘制函数
void DrawRectangle(cv::Mat& img, cv::Rect box)
{
	rectangle(img, box.tl(),box.br(), Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));
}

//鼠标回调函数，根据不同的鼠标事件进行不同的操作
void on_MouseHandle(int event, int x, int y, int flags, void* param)
{
	Mat& image = *(cv::Mat*)param;
	switch (event)
	{
	case EVENT_MOUSEMOVE: //鼠标移动消息
	{
		//如果是否进行绘制的标识符为真，则记录下长和宽到RECT型变量
		if (g_bDrawingBox) {
			g_rectangle.width = x - g_rectangle.x;
			g_rectangle.height = y - g_rectangle.y;
		}
	}
	break;

	case EVENT_LBUTTONDOWN: //左键按下消息
	{
		g_bDrawingBox = true;
		g_rectangle = Rect(x, y, 0, 0); //记录起始点
	}
	break;

	case EVENT_LBUTTONUP: //左键抬起消息
	{
		g_bDrawingBox = false;
		if (g_rectangle.width < 0) {
			g_rectangle.x += g_rectangle.width;
			g_rectangle.width *= -1;
		}
		if (g_rectangle.height < 0) {
			g_rectangle.y += g_rectangle.height;
			g_rectangle.height *= -1;
		}
		//调用函数进行绘制
		DrawRectangle(image, g_rectangle);
	}
	break;
	default:
		break;
	}
}

//主函数
int main(int argc, char** argv)
{
	g_rectangle = Rect(-1, -1, 0, 0);
	Mat srcImage(600, 800, CV_8UC3);
	Mat tempImage;
	srcImage.copyTo(tempImage);
	g_rectangle = Rect(-1, -1, 0, 0);
	srcImage = Scalar::all(0);

	//设置鼠标操作回调函数
	namedWindow(WINDOW_NAME);
	setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*)&srcImage);

	//程序主循环，当进行绘制的标识符为真时，进行绘制
	while (1) {
		srcImage.copyTo(tempImage);
		if (g_bDrawingBox) {
			DrawRectangle(tempImage, g_rectangle);
		}
		imshow(WINDOW_NAME, tempImage);
		if (waitKey(10) == 27) {////按下ESC键，程序退出
			break;
		}
	}
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
