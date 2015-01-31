#include "Pic.h"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Pic::Pic(string filename)
{
	this -> filename = "./pic/" + filename;

	sPic_winname = "源图像";
	dPic_winname = "目标图像";

	namedWindow(sPic_winname);
	namedWindow(dPic_winname);
}

Pic::~Pic(void)
{
    destroyAllWindows();
}

//函数名称：load()
//函数功能：加载并显示原始图片
//输入参数：无
//返回参数：无
void Pic::load()
{
	sPic = imread(filename,CV_LOAD_IMAGE_COLOR);

	imshow(sPic_winname,sPic);
}

//函数名称：prehandle()
//函数功能：在原始图像的基础上进行预处理；
//		   此处不涉及到本项目的核心内容，因此不做具体算法分析
//输入参数：无
//返回参数：无
void Pic::prehandle()
{
	sPic = imread(filename,CV_LOAD_IMAGE_GRAYSCALE);		//提取原图像,并灰度化

	GaussianBlur(sPic,tPic,Size(11,11),0,0);                //高斯平滑滤波，轻微滤波

    Canny(tPic,tPic,100,100);								//Canny算子获取边缘

    imshow("边缘",tPic);
}

//函数名称：position()
//函数功能：预处理图像基础上进行车牌定位；
//		   此处不涉及到本项目的核心内容，因此不做具体算法分析
//输入参数：无
//返回参数：无
void Pic::position()
{
	Mat ele = Mat::ones(20,20,CV_8U);

	for(int i = 0;i < 1;i++)                                //开闭操作
	{
	    morphologyEx(tPic,tPic,MORPH_CLOSE,ele);
        morphologyEx(tPic,tPic,MORPH_OPEN,ele);
	}
	imshow("开闭操作",tPic);
}
