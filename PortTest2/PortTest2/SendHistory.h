#pragma once
#include "afxwin.h"


// CSendHistory �Ի���

class CSendHistory : public CDialogEx
{
	DECLARE_DYNAMIC(CSendHistory)

public:
	CSendHistory(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSendHistory();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HISTORY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��ʾ��ʷ��¼�ľ�̬�ı���
//	CStatic m_Static;
	// ��ʷ��¼���ַ���
	CString m_HistoryText;
};
