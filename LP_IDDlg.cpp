
// LP_IDDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LP_ID.h"
#include "LP_IDDlg.h"
#include "afxdialogex.h"
#include "Pic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLP_IDDlg �Ի���



CLP_IDDlg::CLP_IDDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLP_IDDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLP_IDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLP_IDDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CLP_IDDlg::OnOpenPicture)
	ON_BN_CLICKED(IDC_BUTTON2, &CLP_IDDlg::OnPrehandle)
	ON_BN_CLICKED(IDC_BUTTON3, &CLP_IDDlg::OnPlatePosition)
	ON_BN_CLICKED(IDOK, &CLP_IDDlg::OnCloseAllWindows)
	ON_BN_CLICKED(IDC_BUTTON4, &CLP_IDDlg::OnCharDivision)
	ON_BN_CLICKED(IDC_BUTTON5, &CLP_IDDlg::OnCharIdentify)
END_MESSAGE_MAP()


// CLP_IDDlg ��Ϣ�������

BOOL CLP_IDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CLP_IDDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLP_IDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLP_IDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//��ͼƬ
void CLP_IDDlg::OnOpenPicture()
{
	//����ѡ��.jpg��.bmp�ļ��Ŀؼ�
	CFileDialog dlg(TRUE, _T("*.bmp"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image file(*.bmp;*.jpg)|*.bmp;*.jpg|All Files(*.*)|*.*||"), NULL);
	dlg.m_ofn.lpstrTitle = _T("Open Image");

	//���ѡ����һ���ļ�
	if (dlg.DoModal() == IDOK){
		//��ȡѡ���ļ���·��
		CString filename = dlg.GetPathName();
		//���ò���ʾ��ͼ��
		if (picture.load(filename.GetBuffer(filename.GetLength()))){
			imshow(picture.getSourceWinName(), picture.getSourceMat());
		}
		else{
			MessageBox("��ͼƬʧ��");
		}
		filename.ReleaseBuffer(-1);
	}
}

//ͼ��Ԥ����
void CLP_IDDlg::OnPrehandle()
{
	if (PIC_OPENFILE == picture.getCurrentFlag())
		picture.prehandle();
	else
		MessageBox("���ȴ�ͼƬ");
}

//���ƶ�λ
void CLP_IDDlg::OnPlatePosition()
{
	if (PIC_PREHANDLE == picture.getCurrentFlag())
		picture.position();
	else
		MessageBox("���Ƚ���ͼ��Ԥ����");
}


void CLP_IDDlg::OnCharDivision()
{
	if (PIC_POSITION == picture.getCurrentFlag())
		picture.division();
	else
		MessageBox("���Ƚ��г��ƶ�λ");
}


void CLP_IDDlg::OnCharIdentify()
{
	// TODO: Add your control notification handler code here
}


//�ر����д���
void CLP_IDDlg::OnCloseAllWindows()
{
	picture.closeAllImage();
}