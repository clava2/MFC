
// PortTestDlg.h : ͷ�ļ�
//

#pragma once

#include <PComm/PCOMM.H>

// CPortTestDlg �Ի���
class CPortTestDlg : public CDialogEx
{
// ����
public:
	CPortTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PORTTEST_DIALOG };
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
	CString m_Send;
	CString m_Receive;
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonReceive();
//	afx_msg void OnButtonReceive();
	afx_msg void OnButtonReceive();
};
