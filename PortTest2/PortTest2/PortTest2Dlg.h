
// PortTest2Dlg.h : 头文件
//

#pragma once
#include <PComm/PCOMM.H>
#include "SendHistory.h"

const int OUT_BUFFER_LENGTH = 512;


// CPortTest2Dlg 对话框
class CPortTest2Dlg : public CDialogEx
{
// 构造
public:
	CPortTest2Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PORTTEST2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSend();
	// 需要发送的字符串
	CString m_Send;
	// 接收到的字符串
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
