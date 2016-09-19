// Thread.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCTest.h"
#include "Thread.h"

int m_Num = 0;
CRect m_WindowRect;
int m_XPos = -100;
int m_YPos = -50;


// CThread

IMPLEMENT_DYNCREATE(CThread, CWinThread)

CThread::CThread()
{
	for (int i = 0; i != ALL_WINDOW; i++)
	{
		m_Wnds[i] = NULL;
	}
}

CThread::~CThread()
{
	for (int i = 0; i != ALL_WINDOW; i++)
	{
		if (m_Wnds[i])
		{
			m_Wnds[i]->DestroyWindow();
			delete m_Wnds[i];
			m_Wnds[i] = NULL;
		}
	}
}

BOOL CThread::InitInstance()
{

	if (m_Num < ALL_WINDOW)
	{
		m_XPos += 100;
		m_YPos += 50;
		m_Num++;


		CString WindowTitle, WindowPos, WindowTime;
		m_WindowRect = { m_XPos,m_YPos,WINDOW_WIDTH+m_XPos,WINDOW_HEIGHT+m_YPos };
		WindowTitle.Format(L"窗口%d", m_Num);
		WindowPos.Format(L"创建时的窗口的X坐标为%d,Y坐标为%d", m_XPos, m_YPos);
		m_BeginTime[m_Num] = GetTickCount();

		m_Wnds[m_Num] = new CFrameWnd();
		m_Wnds[m_Num]->Create(NULL, WindowTitle, WS_CAPTION, m_WindowRect);
		m_Wnds[m_Num]->ShowWindow(SW_SHOW);
		m_Wnds[m_Num]->UpdateWindow();
		CClientDC dc(m_Wnds[m_Num]);

		while(1)
		{
			m_NowTime = GetTickCount();
			WindowTime.Format(L"当前窗口创建时间：%d,当前窗口已经创建了%d秒", m_BeginTime[m_Num], (m_NowTime - m_BeginTime[m_Num]) / 1000);
			dc.TextOutW(10, 20, WindowPos);
			dc.TextOutW(10, 40, WindowTime);
			Sleep(50);
		}
	}
	else
	{
		MessageBox(NULL, L"当前创建的窗口过多！", L"Tips", MB_ABORTRETRYIGNORE);
	}

	// TODO:    在此执行任意逐线程初始化
	return TRUE;
}

int CThread::ExitInstance()
{
	// TODO:    在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThread, CWinThread)
END_MESSAGE_MAP()


// CThread 消息处理程序
