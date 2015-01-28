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
	void load();							//���ز���ʾͼƬ
	void prehandle();						//ͼ��Ԥ����
	void position();                        //���ƶ�λ

public:
	string filename;						//�ļ�����

	Mat sPic;								//ԭʼͼ������
	Mat tPic;								//��ʱͼ������
	Mat dPic;								//Ŀ��ͼ������

	string sPic_winname;					//ԭʼͼƬ��������
	string dPic_winname;					//Ŀ��ͼƬ��������
};
