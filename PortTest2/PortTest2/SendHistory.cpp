// SendHistory.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PortTest2.h"
#include "SendHistory.h"
#include "afxdialogex.h"


// CSendHistory �Ի���

IMPLEMENT_DYNAMIC(CSendHistory, CDialogEx)

CSendHistory::CSendHistory(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_HISTORY, pParent)
	, m_HistoryText(_T(""))
{

}

CSendHistory::~CSendHistory()
{
}

void CSendHistory::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_STATIC_HISTORY, m_Static);
	DDX_Text(pDX, IDC_STATIC_HISTORY, m_HistoryText);
}


BEGIN_MESSAGE_MAP(CSendHistory, CDialogEx)
END_MESSAGE_MAP()


// CSendHistory ��Ϣ�������
