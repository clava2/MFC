
// PortTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PortTest.h"
#include "PortTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPortTestDlg 对话框



CPortTestDlg::CPortTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PORTTEST_DIALOG, pParent)
	, m_Send(_T(""))
	, m_Receive(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPortTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEND, m_Send);
	DDX_Text(pDX, IDC_EDIT_RECEIVE, m_Receive);
}

BEGIN_MESSAGE_MAP(CPortTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CPortTestDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_RECEIVE, &CPortTestDlg::OnBnClickedButtonReceive)
//	ON_COMMAND(IDC_BUTTON_RECEIVE, &CPortTestDlg::OnButtonReceive)
ON_COMMAND(IDC_BUTTON_RECEIVE, &CPortTestDlg::OnButtonReceive)
END_MESSAGE_MAP()


// CPortTestDlg 消息处理程序

BOOL CPortTestDlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPortTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPortTestDlg::OnPaint()
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
HCURSOR CPortTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPortTestDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	int port = 1,result = SIO_OK;
	result = sio_open(port);
	if (result != SIO_OK)
	{
		MessageBox("打开串口失败！");
		return;
	}
	result = sio_ioctl(port, B110, BIT_8 | STOP_1 | P_NONE);
	if (result != SIO_OK)
	{
		MessageBox("设置串口失败！");
		sio_close(port);
		return;
	}

	int Len = 0;
	char Temp = 0;

	for (int i = 0; i != m_Send.GetLength(); i++)
	{
		Temp = m_Send.GetAt(i);
		Len = sio_write(port, &Temp, 1);
		if (Len == 0)
		{
			MessageBox("发送失败！");
		}
	}

	if (Len == 0)
	{
		MessageBox("发送失败");
	}

	sio_close(port);
}


void CPortTestDlg::OnButtonReceive()
{
	// TODO: 在此添加命令处理程序代码
}
