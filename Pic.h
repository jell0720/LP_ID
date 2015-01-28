#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Pic
{
public:
	Pic(string filename);
	~Pic();
	void load();							//加载并显示图片
	void prehandle();						//图像预处理
	void position();                        //车牌定位

public:
	string filename;						//文件名称

	Mat sPic;								//原始图像数据
	Mat tPic;								//临时图像数据
	Mat dPic;								//目标图像数据

	string sPic_winname;					//原始图片窗口名称
	string dPic_winname;					//目标图片窗口名称
};
