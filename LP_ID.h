
// LP_ID.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLP_IDApp: 
// �йش����ʵ�֣������ LP_ID.cpp
//

class CLP_IDApp : public CWinApp
{
public:
	CLP_IDApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLP_IDApp theApp;