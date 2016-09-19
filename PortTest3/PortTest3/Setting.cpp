// Setting.cpp : 实现文件
//

#include "stdafx.h"
#include "PortTest3.h"
#include "Setting.h"
#include "afxdialogex.h"


// CSetting 对话框

IMPLEMENT_DYNAMIC(CSetting, CDialogEx)

CSetting::CSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SETTING, pParent)
{

}

CSetting::~CSetting()
{
}

void CSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PORT, m_Port);
	DDX_Control(pDX, IDC_COMBO_BAUD, m_Baud);
	DDX_Control(pDX, IDC_COMBO_DATABIT, m_DataBit);
	DDX_Control(pDX, IDC_COMBO_STOPBIT, m_StopBit);
	DDX_Control(pDX, IDC_COMBO_PARITY, m_Parity);
}


BEGIN_MESSAGE_MAP(CSetting, CDialogEx)
//	ON_CBN_SELCHANGE(IDC_COMBO_PORT, &CSetting::OnCbnSelchangeComboPort)
END_MESSAGE_MAP()


// CSetting 消息处理程序


BOOL CSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化


	m_Port.AddString("COM1");
	m_Port.AddString("COM2");
	m_Port.AddString("COM3");
	m_Port.AddString("COM4");
	m_Port.AddString("COM5");
	m_Port.AddString("COM6");
	m_Port.AddString("COM7");
	m_Port.AddString("COM8");

	m_Baud.AddString("B50");
	m_Baud.AddString("B75");
	m_Baud.AddString("B110");
	m_Baud.AddString("B134");
	m_Baud.AddString("B150");
	m_Baud.AddString("B300");
	m_Baud.AddString("B600");
	m_Baud.AddString("B1200");
	m_Baud.AddString("B1800");
	m_Baud.AddString("B2400");
	m_Baud.AddString("B4800");
	m_Baud.AddString("B7200");
	m_Baud.AddString("B9600");
	m_Baud.AddString("B19200");
	m_Baud.AddString("B38400");
	m_Baud.AddString("B57600");
	m_Baud.AddString("B115200");
	m_Baud.AddString("B230400");
	m_Baud.AddString("B460800");
	m_Baud.AddString("B921600");

	m_DataBit.AddString("BIT_5");
	m_DataBit.AddString("BIT_6");
	m_DataBit.AddString("BIT_7");
	m_DataBit.AddString("BIT_8");

	m_StopBit.AddString("STOP_1");
	m_StopBit.AddString("STOP_2");
	m_StopBit.AddString("STOPBITS_10");
	m_StopBit.AddString("STOPBITS_15");
	m_StopBit.AddString("STOPBITS_20");

	m_Parity.AddString("P_NONE 无");
	m_Parity.AddString("P_DETACH 分离");
	m_Parity.AddString("P_EVEN 偶数");
	m_Parity.AddString("P_MRK 标志");
	m_Parity.AddString("P_NOWAIT 不等待");
	m_Parity.AddString("P_NOWAITO 不等待奇数位");
	m_Parity.AddString("P_ODD 奇数");
	m_Parity.AddString("P_OVERLAY 覆盖");
	m_Parity.AddString("P_SPC 空格");
	m_Parity.AddString("P_WAIT 等待");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CSetting::SetValue(int& Port, int& Baud, int& DataBit, int& StopBit, int& Parity)
{
	DoModal();
	UpdateData(true);
	int m = m_Port.GetCurSel();
	CString str;
	str.Format("%d", m);
	MessageBox(str);
}


//void CSetting::OnCbnSelchangeComboPort()
//{
//	// TODO: 在此添加控件通知处理程序代码
//
//
//}
