/*M///////////////////////////////////////////////////////////////////////////////////////
//
//��Ŀ���ƣ����Ʒָ�V1.0 ID_Project_V1_0
//
//����ʱ�䣺2015/1/7
//
//�������ߣ��� ��
//
//��Ŀ���ݣ�����Ŀ��Ҫ������֤��ͬ�㷨���ڳ����ַ��ָ��Ч���Ĳ��죬ͬʱ�ҳ���ͬ���㷨�����Էָ�Ч��
//		   ��Ӱ�죬���ҳ������㷨��
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
