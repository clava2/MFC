
// PortTest3Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PortTest3.h"
#include "PortTest3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int READ_BUFFER_LENGTH = 256;
bool Listening = false;
char ReadBuffer[READ_BUFFER_LENGTH];

const int INTERNAL = 200;


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


// CPortTest3Dlg 对话框



CPortTest3Dlg::CPortTest3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PORTTEST3_DIALOG, pParent)
	, m_Send(_T(""))
	,m_Port(1)
	,m_Thread(INVALID_HANDLE_VALUE)
	, m_Receive(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPortTest3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEND, m_Send);
	DDX_Control(pDX, IDC_BUTTON_OPEN, m_ButtonOpen);
	DDX_Text(pDX, IDC_EDIT_RECEIVE, m_Receive);
	DDX_Control(pDX, IDC_BUTTON_CLEAR, m_ButtonClear);
}

BEGIN_MESSAGE_MAP(CPortTest3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CPortTest3Dlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CPortTest3Dlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_HISTORY, &CPortTest3Dlg::OnBnClickedButtonHistory)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CPortTest3Dlg::OnBnClickedButtonSetting)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CPortTest3Dlg::OnBnClickedButtonClear)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CPortTest3Dlg 消息处理程序

BOOL CPortTest3Dlg::OnInitDialog()
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

	SetTimer(1, INTERNAL, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPortTest3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPortTest3Dlg::OnPaint()
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
HCURSOR CPortTest3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPortTest3Dlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码

	if (!Listening)
	{
		MessageBox("串口还没有打开！");
		return;
	}

	UpdateData(true);
	int result = SIO_OK;
	result = sio_ioctl(m_Port, m_Baud, m_Mode);
	if (result != SIO_OK)
	{
		MessageBox("设置串口失败！");
		return;
	}
	sio_write(m_Port, (char*)m_Send.GetString(), m_Send.GetLength());

	m_History.m_History += m_Send;

	sio_close(m_Port);
	sio_open(m_Port);
}


void CPortTest3Dlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	int result = SIO_OK;

	if (!Listening)
	{

		result = sio_open(m_Port);
		if (result != SIO_OK)
		{
			MessageBox("串口打开失败！");

			return;
		}
		m_ButtonOpen.SetWindowTextA("关闭串口");

		m_Thread = CreateThread(NULL, 0, GetData, this, 0, NULL);

		if (m_Thread == INVALID_HANDLE_VALUE)
		{
			MessageBox("创建新线程失败！");
			return;
		}
		Listening = true;
	}

	else
	{
		result = sio_close(m_Port);
		if (result != SIO_OK)
		{
			MessageBox("串口关闭失败！");
			return;
		}
		Listening = false;
		WaitForSingleObject(m_Thread, 250);
		m_ButtonOpen.SetWindowTextA("打开串口");
	}
}


void CPortTest3Dlg::OnBnClickedButtonHistory()
{
	// TODO: 在此添加控件通知处理程序代码
	m_History.DoModal();
}


void CPortTest3Dlg::OnBnClickedButtonSetting()
{
	// TODO: 在此添加控件通知处理程序代码

	//m_Setting.SetValue(m_Port, m_Baud, m_DataBit, m_StopBit, m_Parity);
}

DWORD CALLBACK GetData(LPVOID pParam)
{
	CPortTest3Dlg* pReceive = (CPortTest3Dlg*)pParam;
	while (Listening)
	{
		memset(ReadBuffer, 0, READ_BUFFER_LENGTH);
		sio_SetReadTimeouts(pReceive->m_Port, 200, 2);
		if (sio_iqueue(pReceive->m_Port))
		{
			pReceive->m_ButtonClear.EnableWindow(true);
			sio_read(pReceive->m_Port, ReadBuffer, READ_BUFFER_LENGTH);
			CString str;
			for (int i = 0; (i < READ_BUFFER_LENGTH) && (ReadBuffer[i]); i++)
			{
				str.Append(ReadBuffer + i, 1);
			}
			pReceive->m_TempText += str;
		}
	}
	return 0;
}


void CPortTest3Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	UpdateData(true);
	m_Receive = m_TempText;
	UpdateData(false);

	CDialogEx::OnTimer(nIDEvent);
}


void CPortTest3Dlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Receive = "";
	m_TempText = "";
	m_ButtonClear.EnableWindow(false);
}


void CPortTest3Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO: 在此处添加消息处理程序代码
	Listening = false;
	WaitForSingleObject(m_Thread, 500);

	KillTimer(1);
}
