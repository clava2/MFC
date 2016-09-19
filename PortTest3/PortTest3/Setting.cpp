// Setting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PortTest3.h"
#include "Setting.h"
#include "afxdialogex.h"


// CSetting �Ի���

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


// CSetting ��Ϣ�������


BOOL CSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��


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

	m_Parity.AddString("P_NONE ��");
	m_Parity.AddString("P_DETACH ����");
	m_Parity.AddString("P_EVEN ż��");
	m_Parity.AddString("P_MRK ��־");
	m_Parity.AddString("P_NOWAIT ���ȴ�");
	m_Parity.AddString("P_NOWAITO ���ȴ�����λ");
	m_Parity.AddString("P_ODD ����");
	m_Parity.AddString("P_OVERLAY ����");
	m_Parity.AddString("P_SPC �ո�");
	m_Parity.AddString("P_WAIT �ȴ�");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
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
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//
//
//}
