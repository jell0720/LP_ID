#include "stdafx.h"
#include "Pic.h"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Pic::Pic()
{
	sPic_winname = "源图像";
	dPic_winname = "目标图像";

	CurrentFlag = PIC_SPACE;
}

Pic::~Pic(void)
{
    destroyAllWindows();
}

//函数名称：load
//函数功能：加载并显示原始图片
//输入参数：string filename为待打开的图片文件路径名称
//返回参数：bool型，true为正确打开，false为打开失败
bool Pic::load(string filepath)
{
	this->filepath = filepath;

	sPic = imread(this->filepath, CV_LOAD_IMAGE_COLOR);

	if (!sPic.data)
		return false;
	else{
		CurrentFlag = PIC_OPENFILE;
		return true;
	}
}

//函数名称：prehandle()
//函数功能：在原始图像的基础上进行预处理；
//		   此处不涉及到本项目的核心内容，因此不做具体算法分析
//输入参数：无
//返回参数：无
void Pic::prehandle()
{
	sPic = imread(filepath, CV_LOAD_IMAGE_GRAYSCALE);		//灰度化

	GaussianBlur(sPic,tPic,Size(11,11),0,0);				//高斯平滑滤波，轻微滤波

    Canny(tPic,tPic,100,100);								//Canny算子获取边缘

    imshow("边缘",tPic);

	CurrentFlag = PIC_PREHANDLE;
}

//函数名称：position()
//函数功能：预处理图像基础上进行车牌定位；
//		   此处不涉及到本项目的核心内容，因此不做具体算法分析
//输入参数：无
//返回参数：无
void Pic::position()
{
	Mat ele = Mat::ones(tPic.rows*9/100,tPic.cols*9/100,CV_8U);

	for(int i = 0;i < 1;i++)                                //开闭操作
	{
	    morphologyEx(tPic,tPic,MORPH_CLOSE,ele);
        morphologyEx(tPic,tPic,MORPH_OPEN,ele);
	}
	imshow("开闭操作",tPic);

	CurrentFlag = PIC_POSITION;
}

//函数名称：closeAllImage()
//函数功能：关闭所有图片窗口
//输入参数：无
//返回参数：无
void Pic::closeAllImage(){
	destroyAllWindows();
	CurrentFlag = PIC_POSITION;
}

//函数名称：getLastMat()
//函数功能：获取最近一次操作结果
//输入参数：无
//返回参数：Mat tPic;
Mat Pic::getLastMat() const{
	return tPic;
}

//函数名称：getMatFlag()
//函数功能：获取当前操作的标志位
//输入参数：无
//返回参数：uchar型,当前的操作所对应的标志
OperationFlag Pic::getCurrentFlag(){
	return CurrentFlag;
}
