
// PortTest2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPortTest2App: 
// �йش����ʵ�֣������ PortTest2.cpp
//

class CPortTest2App : public CWinApp
{
public:
	CPortTest2App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPortTest2App theApp;