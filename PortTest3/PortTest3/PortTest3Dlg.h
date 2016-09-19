
// PortTest3Dlg.h : 头文件
//

#pragma once

#include <PComm\PCOMM.H>
#include "History.h"
#include "Setting.h"

#include "afxwin.h"

// CPortTest3Dlg 对话框
class CPortTest3Dlg : public CDialogEx
{

public:

	HANDLE m_Thread;
	CHistory m_History;
	CSetting m_Setting;

	int m_Port;
	int m_Baud;
	int m_DataBit;
	int m_StopBit;
	int m_Parity;
	int m_Mode;

	CString m_TempText;

// 构造
public:
	CPortTest3Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PORTTEST3_DIALOG };
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



	CString m_Send;
	CString m_Receive;
	CButton m_ButtonOpen;



	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonHistory();
	afx_msg void OnBnClickedButtonSetting();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton m_ButtonClear;
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnDestroy();
};


DWORD CALLBACK GetData(LPVOID pParam);