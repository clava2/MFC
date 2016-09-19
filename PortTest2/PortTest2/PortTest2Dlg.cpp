
// PortTest2Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PortTest2.h"
#include "PortTest2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

char OutBuffer[OUT_BUFFER_LENGTH];
bool Listening = false;
bool QuitThread = false;
CEvent Event;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CPortTest2Dlg �Ի���



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


// CPortTest2Dlg ��Ϣ�������

BOOL CPortTest2Dlg::OnInitDialog()
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	SetTimer(1, 100, NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPortTest2Dlg::OnPaint()
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
HCURSOR CPortTest2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPortTest2Dlg::OnBnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData();
	int result = SIO_OK;
	result = sio_open(m_Port);
	if ((result != SIO_OK) && (!Listening))
	{
		MessageBox("���´���ʧ�ܣ�");
		return;
	}
	result = sio_ioctl(m_Port, m_Baud, m_Mode);
	if (result != SIO_OK)
	{
		MessageBox("���ô���ʧ�ܣ�");
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
			MessageBox("����ʧ�ܣ�");
			sio_close(m_Port);
		}
	}

	if (Len == 0)
	{
		MessageBox("����ʧ��");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!Listening)
	{
		TerminateThread(m_Thread, 0);
		m_Thread = CreateThread(NULL, 0, GetChar, this,  0, NULL);
		if (m_Thread == INVALID_HANDLE_VALUE)
		{
			MessageBox("�޷��������̣߳�");
			return;
		}
		Listening = true;
		QuitThread = false;
	}
	else
	{
		MessageBox("�Ѿ��ڽ��������ˣ����ȹر��ڴ�");
	}
}


void CPortTest2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UpdateData(true);
	m_Receive = m_TempText;
	UpdateData(false);

	CDialogEx::OnTimer(nIDEvent);
}


void CPortTest2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	TerminateThread(m_Thread, 0);
	sio_close(m_Port);
	KillTimer(1);
}


void CPortTest2Dlg::OnBnClickedButtonStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		MessageBox(NULL, "���´���ʧ�ܣ�", "��ʾ", MB_OK);
		return 0;
	}
	result = sio_ioctl(pReceive->m_Port, pReceive->m_Baud, pReceive->m_Mode);
	if (result != SIO_OK)
	{
		MessageBox(NULL, "���ô���ʧ�ܣ�", "��ʾ", MB_OK);
		sio_close(pReceive->m_Port);
		return 0;
	}
	MessageBox(NULL, "�����Ѿ����ڼ���״̬��", "��ʾ", MB_OK);
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
	MessageBox(NULL, "�����Ѿ��˳�����״̬��", "��ʾ", MB_OK);
	return 0;
}



//void CPortTest2Dlg::OnBnClickedButton1()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	History.DoModal();
//}


void CPortTest2Dlg::OnBnClickedButtonHistory()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_History.DoModal();
}


void CPortTest2Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Receive = "";
	m_TempText = "";
}
