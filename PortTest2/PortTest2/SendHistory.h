#pragma once
#include "afxwin.h"


// CSendHistory 对话框

class CSendHistory : public CDialogEx
{
	DECLARE_DYNAMIC(CSendHistory)

public:
	CSendHistory(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSendHistory();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HISTORY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 显示历史记录的静态文本框
//	CStatic m_Static;
	// 历史纪录的字符串
	CString m_HistoryText;
};
