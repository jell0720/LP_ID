
// LP_IDDlg.h : ͷ�ļ�
//

#pragma once
#include "Pic.h"

// CLP_IDDlg �Ի���
class CLP_IDDlg : public CDialogEx
{
// ����
public:
	CLP_IDDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LP_ID_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	Pic picture;
	afx_msg void OnOpenPicture();
	afx_msg void OnPrehandle();
	afx_msg void OnPlatePosition();
	afx_msg void OnCharDivision();
	afx_msg void OnCharIdentify();
	afx_msg void OnCloseAllWindows();
};
