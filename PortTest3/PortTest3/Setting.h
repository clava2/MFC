#pragma once
#include "afxwin.h"


// CSetting 对话框

class CSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CSetting)

public:
	CSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetting();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_Port;
	CComboBox m_Baud;
	CComboBox m_DataBit;
	CComboBox m_StopBit;
	CComboBox m_Parity;
//	afx_msg void OnCbnSelchangeComboPort();
	void SetValue(int& m_Port, int& m_Baud, int& DataBit, int& StopBit, int& Parity);
};
