#pragma once
#include "afxwin.h"


// CSetting �Ի���

class CSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CSetting)

public:
	CSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetting();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
