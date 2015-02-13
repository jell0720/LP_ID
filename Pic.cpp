#include "stdafx.h"
#include "Pic.h"
#include "histogram.h"
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

	GaussianBlur(sPic, tPic, Size(13,13), 0, 0);			//高斯平滑滤波，轻微滤波

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

	for(int i = 0;i < 2;i++)                                //开闭操作
	{
	    morphologyEx(tPic,tPic,MORPH_CLOSE,ele);
        morphologyEx(tPic,tPic,MORPH_OPEN,ele);
	}

	//查找边界
	vector<vector<Point>>contours;
	Mat imageROI(tPic.size(), CV_8U, Scalar(255));
	findContours(tPic,
		contours,
		CV_RETR_EXTERNAL,
		CV_CHAIN_APPROX_NONE);

	vector<vector<Point>>::const_iterator itc = contours.begin();
	unsigned int maxVal = itc->size(),number=0;
	while (itc != contours.end())
	{
		if (itc->size() > maxVal)
			number = distance<vector<vector<Point>>::const_iterator>(contours.begin(), itc);
		itc++;
	}

	Rect r0 = boundingRect(Mat(contours[number]));
	tPic = sPic(r0);

	imshow("ROI", tPic);
	CurrentFlag = PIC_POSITION;
}

void Pic::division(){
	Histogram h;
	imshow("Hist", h.getHistogramImage(tPic));
}

void Pic::closeAllImage(){
	destroyAllWindows();
	CurrentFlag = PIC_POSITION;
}

string Pic::getSourceWinName() const{
	return sPic_winname;
}

string Pic::getDirectionWinName() const{
	return dPic_winname;
}
Mat Pic::getSourceMat() const{
	return sPic;
}

Mat Pic::getDirectionMat() const{
	return dPic;
}

Mat Pic::getLastMat() const{
	return tPic;
}

OperationFlag Pic::getCurrentFlag() const{
	return CurrentFlag;
}
