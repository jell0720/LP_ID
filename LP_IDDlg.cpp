
// LP_IDDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LP_ID.h"
#include "LP_IDDlg.h"
#include "afxdialogex.h"
#include "Pic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CLP_IDDlg 对话框



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


// CLP_IDDlg 消息处理程序

BOOL CLP_IDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLP_IDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLP_IDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//打开图片
void CLP_IDDlg::OnOpenPicture()
{
	//用于选择.jpg和.bmp文件的控件
	CFileDialog dlg(TRUE, _T("*.bmp"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image file(*.bmp;*.jpg)|*.bmp;*.jpg|All Files(*.*)|*.*||"), NULL);
	dlg.m_ofn.lpstrTitle = _T("Open Image");

	//如果选中了一个文件
	if (dlg.DoModal() == IDOK){
		//获取选中文件的路径
		CString filename = dlg.GetPathName();
		//设置并显示该图像
		if (picture.load(filename.GetBuffer(filename.GetLength()))){
			imshow(picture.getSourceWinName(), picture.getSourceMat());
		}
		else{
			MessageBox("打开图片失败");
		}
		filename.ReleaseBuffer(-1);
	}
}

//图像预处理
void CLP_IDDlg::OnPrehandle()
{
	if (PIC_OPENFILE == picture.getCurrentFlag())
		picture.prehandle();
	else
		MessageBox("请先打开图片");
}

//车牌定位
void CLP_IDDlg::OnPlatePosition()
{
	if (PIC_PREHANDLE == picture.getCurrentFlag())
		picture.position();
	else
		MessageBox("请先进行图像预处理");
}


void CLP_IDDlg::OnCharDivision()
{
	if (PIC_POSITION == picture.getCurrentFlag())
		picture.division();
	else
		MessageBox("请先进行车牌定位");
}


void CLP_IDDlg::OnCharIdentify()
{
	// TODO: Add your control notification handler code here
}


//关闭所有窗口
void CLP_IDDlg::OnCloseAllWindows()
{
	picture.closeAllImage();
}