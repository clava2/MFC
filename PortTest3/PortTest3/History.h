#pragma once


// CHistory 对话框

class CHistory : public CDialogEx
{
	DECLARE_DYNAMIC(CHistory)

public:
	CHistory(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHistory();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_History;
};
