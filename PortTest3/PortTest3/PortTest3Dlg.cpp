
// PortTest3Dlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

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


// CPortTest3Dlg �Ի���



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


// CPortTest3Dlg ��Ϣ�������

BOOL CPortTest3Dlg::OnInitDialog()
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

	SetTimer(1, INTERNAL, NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPortTest3Dlg::OnPaint()
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
HCURSOR CPortTest3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPortTest3Dlg::OnBnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if (!Listening)
	{
		MessageBox("���ڻ�û�д򿪣�");
		return;
	}

	UpdateData(true);
	int result = SIO_OK;
	result = sio_ioctl(m_Port, m_Baud, m_Mode);
	if (result != SIO_OK)
	{
		MessageBox("���ô���ʧ�ܣ�");
		return;
	}
	sio_write(m_Port, (char*)m_Send.GetString(), m_Send.GetLength());

	m_History.m_History += m_Send;

	sio_close(m_Port);
	sio_open(m_Port);
}


void CPortTest3Dlg::OnBnClickedButtonOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int result = SIO_OK;

	if (!Listening)
	{

		result = sio_open(m_Port);
		if (result != SIO_OK)
		{
			MessageBox("���ڴ�ʧ�ܣ�");

			return;
		}
		m_ButtonOpen.SetWindowTextA("�رմ���");

		m_Thread = CreateThread(NULL, 0, GetData, this, 0, NULL);

		if (m_Thread == INVALID_HANDLE_VALUE)
		{
			MessageBox("�������߳�ʧ�ܣ�");
			return;
		}
		Listening = true;
	}

	else
	{
		result = sio_close(m_Port);
		if (result != SIO_OK)
		{
			MessageBox("���ڹر�ʧ�ܣ�");
			return;
		}
		Listening = false;
		WaitForSingleObject(m_Thread, 250);
		m_ButtonOpen.SetWindowTextA("�򿪴���");
	}
}


void CPortTest3Dlg::OnBnClickedButtonHistory()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_History.DoModal();
}


void CPortTest3Dlg::OnBnClickedButtonSetting()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	UpdateData(true);
	m_Receive = m_TempText;
	UpdateData(false);

	CDialogEx::OnTimer(nIDEvent);
}


void CPortTest3Dlg::OnBnClickedButtonClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Receive = "";
	m_TempText = "";
	m_ButtonClear.EnableWindow(false);
}


void CPortTest3Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO: �ڴ˴������Ϣ����������
	Listening = false;
	WaitForSingleObject(m_Thread, 500);

	KillTimer(1);
}
