/*M///////////////////////////////////////////////////////////////////////////////////////
//
//项目名称：车牌分割V1.0 ID_Project_V1_0
//
//创建时间：2015/1/7
//
//代码作者：宋 安
//
//项目内容：本项目主要用于验证不同算法对于车牌字符分割的效果的差异，同时找出不同的算法参数对分割效果
//		   的影响，以找出最优算法。
//
//M*/

#include <iostream>
#include <opencv2/opencv.hpp>
#include "Pic.h"

using namespace std;
using namespace cv;


int main()
{
	Pic pic1("src1.jpg");

	pic1.load();
	pic1.prehandle();
	//pic1.position();

	waitKey(0);
	return 0;
}
