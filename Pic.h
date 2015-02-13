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
	bool load(string filepath);				//���ز���ʾͼƬ
	void prehandle();						//ͼ��Ԥ����
	void position();						//���ƶ�λ
	void division();						//���Ʒָ�
	void identify();						//����ʶ��
	void closeAllImage();					//�ر�����ͼƬ����

	string getSourceWinName() const;		//��ȡԭͼƬ��������
	string getDirectionWinName() const;		//��ȡĿ��ͼƬ��������
	Mat getSourceMat() const;				//��ȡԭͼ��
	Mat getDirectionMat() const;			//��ȡĿ��ͼ��
	OperationFlag getCurrentFlag () const;	//��ȡ��ǰ�����ı�־λ
	Mat getLastMat() const;					//��ȡ���һ�ν��

private:
	string filepath;						//ͼ���ļ�����

	Mat sPic;								//ԭʼͼ������
	Mat tPic;								//��ʱͼ������
	Mat dPic;								//Ŀ��ͼ������

	string sPic_winname;					//ԭʼͼƬ��������
	string dPic_winname;					//Ŀ��ͼƬ��������

	OperationFlag CurrentFlag;				//��ǰ������Ӧ�ı�־
	
};
