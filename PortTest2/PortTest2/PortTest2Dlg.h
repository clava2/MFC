
// PortTest2Dlg.h : ͷ�ļ�
//

#pragma once
#include <PComm/PCOMM.H>
#include "SendHistory.h"

const int OUT_BUFFER_LENGTH = 512;


// CPortTest2Dlg �Ի���
class CPortTest2Dlg : public CDialogEx
{
// ����
public:
	CPortTest2Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PORTTEST2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSend();
	// ��Ҫ���͵��ַ���
	CString m_Send;
	// ���յ����ַ���
	CString m_Receive;

	CString m_TempText;

	CSendHistory m_History;

	int m_Port;
	int m_Baud;
	int m_DataBit;
	int m_StopBit;
	int m_Poriaty;
	int m_Mode;

	HANDLE m_Thread;
	afx_msg void OnBnClickedButtonReceive();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonStop();
//	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonHistory();
	afx_msg void OnBnClickedButton1();
};

DWORD CALLBACK GetChar(LPVOID pParam);
