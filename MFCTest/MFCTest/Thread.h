#pragma once


const int ALL_WINDOW = 10;

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;



// CThread

class CThread : public CWinThread
{
	DECLARE_DYNCREATE(CThread)

public:

	CFrameWnd* m_Wnds[ALL_WINDOW];

	long m_BeginTime[ALL_WINDOW];
	long m_NowTime;

protected:
	CThread();           // 动态创建所使用的受保护的构造函数
	virtual ~CThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


