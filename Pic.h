#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

typedef enum{
	PIC_SPACE,
	PIC_OPENFILE,
	PIC_PREHANDLE,
	PIC_POSITION,
	PIC_DIVISION,
	PIC_IDENTIFY
}OperationFlag;

class Pic
{
public:
	Pic();
	~Pic();
	bool load(string filepath);				//加载并显示图片
	void prehandle();						//图像预处理
	void position();						//车牌定位
	void division();						//车牌分割
	void identify();						//车牌识别
	void closeAllImage();					//关闭所有图片窗口

	string getSourceWinName() const;		//获取原图片窗口名称
	string getDirectionWinName() const;		//获取目标图片窗口名称
	Mat getSourceMat() const;				//获取原图像
	Mat getDirectionMat() const;			//获取目标图像
	OperationFlag getCurrentFlag () const;	//获取当前操作的标志位
	Mat getLastMat() const;					//获取最近一次结果

private:
	string filepath;						//图像文件名称

	Mat sPic;								//原始图像数据
	Mat tPic;								//临时图像数据
	Mat dPic;								//目标图像数据

	string sPic_winname;					//原始图片窗口名称
	string dPic_winname;					//目标图片窗口名称

	OperationFlag CurrentFlag;				//当前操作对应的标志
	
};
