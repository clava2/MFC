// History.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PortTest3.h"
#include "History.h"
#include "afxdialogex.h"


// CHistory �Ի���

IMPLEMENT_DYNAMIC(CHistory, CDialogEx)

CHistory::CHistory(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_History(_T(""))
{

}

CHistory::~CHistory()
{
}

void CHistory::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_History);
}


BEGIN_MESSAGE_MAP(CHistory, CDialogEx)
END_MESSAGE_MAP()


// CHistory ��Ϣ�������
