#include "Pic.h"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Pic::Pic(string filename)
{
	this -> filename = "./pic/" + filename;

	sPic_winname = "Դͼ��";
	dPic_winname = "Ŀ��ͼ��";

	namedWindow(sPic_winname);
	namedWindow(dPic_winname);
}

Pic::~Pic(void)
{
    destroyAllWindows();
}

//�������ƣ�load()
//�������ܣ����ز���ʾԭʼͼƬ
//�����������
//���ز�������
void Pic::load()
{
	sPic = imread(filename,CV_LOAD_IMAGE_COLOR);

	imshow(sPic_winname,sPic);
}

//�������ƣ�prehandle()
//�������ܣ���ԭʼͼ��Ļ����Ͻ���Ԥ����
//		   �˴����漰������Ŀ�ĺ������ݣ���˲��������㷨����
//�����������
//���ز�������
void Pic::prehandle()
{
	sPic = imread(filename,CV_LOAD_IMAGE_GRAYSCALE);		//��ȡԭͼ��,���ҶȻ�

	GaussianBlur(sPic,tPic,Size(11,11),0,0);                //��˹ƽ���˲�����΢�˲�

    Canny(tPic,tPic,100,100);								//Canny���ӻ�ȡ��Ե

    imshow("��Ե",tPic);
}

//�������ƣ�position()
//�������ܣ�Ԥ����ͼ������Ͻ��г��ƶ�λ��
//		   �˴����漰������Ŀ�ĺ������ݣ���˲��������㷨����
//�����������
//���ز�������
void Pic::position()
{
	Mat ele = Mat::ones(20,20,CV_8U);

	for(int i = 0;i < 1;i++)                                //���ղ���
	{
	    morphologyEx(tPic,tPic,MORPH_CLOSE,ele);
        morphologyEx(tPic,tPic,MORPH_OPEN,ele);
	}
	imshow("���ղ���",tPic);
}
