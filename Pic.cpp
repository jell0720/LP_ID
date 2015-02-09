#include "stdafx.h"
#include "Pic.h"
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

	GaussianBlur(sPic,tPic,Size(11,11),0,0);				//��˹ƽ���˲�����΢�˲�

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

	for(int i = 0;i < 1;i++)                                //���ղ���
	{
	    morphologyEx(tPic,tPic,MORPH_CLOSE,ele);
        morphologyEx(tPic,tPic,MORPH_OPEN,ele);
	}
	imshow("���ղ���",tPic);

	CurrentFlag = PIC_POSITION;
}

//�������ƣ�closeAllImage()
//�������ܣ��ر�����ͼƬ����
//�����������
//���ز�������
void Pic::closeAllImage(){
	destroyAllWindows();
	CurrentFlag = PIC_POSITION;
}

//�������ƣ�getLastMat()
//�������ܣ���ȡ���һ�β������
//�����������
//���ز�����Mat tPic;
Mat Pic::getLastMat() const{
	return tPic;
}

//�������ƣ�getMatFlag()
//�������ܣ���ȡ��ǰ�����ı�־λ
//�����������
//���ز�����uchar��,��ǰ�Ĳ�������Ӧ�ı�־
OperationFlag Pic::getCurrentFlag(){
	return CurrentFlag;
}
