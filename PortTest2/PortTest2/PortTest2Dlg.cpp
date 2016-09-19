
// PortTest2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PortTest2.h"
#include "PortTest2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

char OutBuffer[OUT_BUFFER_LENGTH];
bool Listening = false;
bool QuitThread = false;
CEvent Event;

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


// CPortTest2Dlg 对话框



CPortTest2Dlg::CPortTest2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PORTTEST2_DIALOG, pParent)
	, m_Send(_T(""))
	, m_Receive(_T(""))
	, m_Port(1)
	, m_Baud(B110)
	, m_DataBit(BIT_8)
	, m_StopBit(STOP_1)
	, m_Poriaty(P_NONE)
	,m_Mode(m_DataBit|m_StopBit|m_Poriaty)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	for (int i = 0; i != OUT_BUFFER_LENGTH; i++)
	{
		OutBuffer[i] = 0;
	}
	m_Thread = INVALID_HANDLE_VALUE;
}

void CPortTest2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEND, m_Send);
	DDX_Text(pDX, IDC_EDIT_RECEIVE, m_Receive);
}

BEGIN_MESSAGE_MAP(CPortTest2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CPortTest2Dlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_RECEIVE, &CPortTest2Dlg::OnBnClickedButtonReceive)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CPortTest2Dlg::OnBnClickedButtonStop)
//	ON_BN_CLICKED(IDC_BUTTON1, &CPortTest2Dlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON_HISTORY, &CPortTest2Dlg::OnBnClickedButtonHistory)
ON_BN_CLICKED(IDC_BUTTON1, &CPortTest2Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CPortTest2Dlg 消息处理程序

BOOL CPortTest2Dlg::OnInitDialog()
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

	SetTimer(1, 100, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPortTest2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPortTest2Dlg::OnPaint()
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
HCURSOR CPortTest2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPortTest2Dlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData();
	int result = SIO_OK;
	result = sio_open(m_Port);
	if ((result != SIO_OK) && (!Listening))
	{
		MessageBox("打开新串口失败！");
		return;
	}
	result = sio_ioctl(m_Port, m_Baud, m_Mode);
	if (result != SIO_OK)
	{
		MessageBox("设置串口失败！");
		sio_close(m_Port);
		return;
	}

	int Len = 0;
	char Temp = 0;

	for (int i = 0; i != m_Send.GetLength(); i++)
	{
		Temp = m_Send.GetAt(i);
		Len = sio_write(m_Port, &Temp, 1);
		if (Len == 0)
		{
			MessageBox("发送失败！");
			sio_close(m_Port);
		}
	}

	if (Len == 0)
	{
		MessageBox("发送失败");
		sio_close(m_Port);
	}

	//m_History.m_HistoryText = m_Send + '\n';
	if (!Listening)
	{
		sio_close(m_Port);
	}

}



void CPortTest2Dlg::OnBnClickedButtonReceive()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!Listening)
	{
		TerminateThread(m_Thread, 0);
		m_Thread = CreateThread(NULL, 0, GetChar, this,  0, NULL);
		if (m_Thread == INVALID_HANDLE_VALUE)
		{
			MessageBox("无法创建新线程！");
			return;
		}
		Listening = true;
		QuitThread = false;
	}
	else
	{
		MessageBox("已经在接收数据了！请先关闭在打开");
	}
}


void CPortTest2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UpdateData(true);
	m_Receive = m_TempText;
	UpdateData(false);

	CDialogEx::OnTimer(nIDEvent);
}


void CPortTest2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	TerminateThread(m_Thread, 0);
	sio_close(m_Port);
	KillTimer(1);
}


void CPortTest2Dlg::OnBnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码
	QuitThread = true;
	Listening = false;
}

DWORD CALLBACK GetChar(LPVOID pParam)
{
	CPortTest2Dlg* pReceive = (CPortTest2Dlg*)pParam;
	int result = SIO_OK;
	result = sio_open(pReceive->m_Port);
	if (result != SIO_OK)
	{
		MessageBox(NULL, "打开新串口失败！", "提示", MB_OK);
		return 0;
	}
	result = sio_ioctl(pReceive->m_Port, pReceive->m_Baud, pReceive->m_Mode);
	if (result != SIO_OK)
	{
		MessageBox(NULL, "设置串口失败！", "提示", MB_OK);
		sio_close(pReceive->m_Port);
		return 0;
	}
	MessageBox(NULL, "串口已经处于监听状态！", "提示", MB_OK);
	while (!QuitThread)
	{
		sio_SetReadTimeouts(pReceive->m_Port, 200, 2);
		if (sio_iqueue(pReceive->m_Port))
		{
			sio_read(pReceive->m_Port, OutBuffer, OUT_BUFFER_LENGTH);
			CString str;
			for (int i = 0; i != OUT_BUFFER_LENGTH; i++)
			{
				str.Append(OutBuffer+i,1);
			}
			pReceive->m_TempText += str;
		}
		memset(OutBuffer, 0, OUT_BUFFER_LENGTH);
	}
	MessageBox(NULL, "串口已经退出监听状态！", "提示", MB_OK);
	return 0;
}



//void CPortTest2Dlg::OnBnClickedButton1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	History.DoModal();
//}


void CPortTest2Dlg::OnBnClickedButtonHistory()
{
	// TODO: 在此添加控件通知处理程序代码
	m_History.DoModal();
}


void CPortTest2Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Receive = "";
	m_TempText = "";
}
