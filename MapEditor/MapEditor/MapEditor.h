
// MapEditor.h : MapEditor Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

#include <gdiplus.h>

using namespace Gdiplus;


// CMapEditorApp:
// �йش����ʵ�֣������ MapEditor.cpp
//

class CMapEditorApp : public CWinApp
{
public:
	ULONG_PTR m_GdiplusToken;
public:
	CMapEditorApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMapEditorApp theApp;