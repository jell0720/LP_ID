#include "stdafx.h"
#include "Pic.h"
#include "histogram.h"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Pic::Pic()
{
	sPic_winname = "Դͼ��";
	dPic_winname = "Ŀ��ͼ��";

	CurrentFlag = PIC_SPACE;
}

Pic::~Pic(void)
{
    destroyAllWindows();
}

//�������ƣ�load
//�������ܣ����ز���ʾԭʼͼƬ
//���������string filenameΪ���򿪵�ͼƬ�ļ�·������
//���ز�����bool�ͣ�trueΪ��ȷ�򿪣�falseΪ��ʧ��
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

//�������ƣ�prehandle()
//�������ܣ���ԭʼͼ��Ļ����Ͻ���Ԥ����
//		   �˴����漰������Ŀ�ĺ������ݣ���˲��������㷨����
//�����������
//���ز�������
void Pic::prehandle()
{
	sPic = imread(filepath, CV_LOAD_IMAGE_GRAYSCALE);		//�ҶȻ�

	GaussianBlur(sPic, tPic, Size(13,13), 0, 0);			//��˹ƽ���˲�����΢�˲�

    Canny(tPic,tPic,100,100);								//Canny���ӻ�ȡ��Ե

    imshow("��Ե",tPic);

	CurrentFlag = PIC_PREHANDLE;
}

//�������ƣ�position()
//�������ܣ�Ԥ����ͼ������Ͻ��г��ƶ�λ��
//		   �˴����漰������Ŀ�ĺ������ݣ���˲��������㷨����
//�����������
//���ز�������
void Pic::position()
{
	Mat ele = Mat::ones(tPic.rows*9/100,tPic.cols*9/100,CV_8U);

	for(int i = 0;i < 2;i++)                                //���ղ���
	{
	    morphologyEx(tPic,tPic,MORPH_CLOSE,ele);
        morphologyEx(tPic,tPic,MORPH_OPEN,ele);
	}

	//���ұ߽�
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
