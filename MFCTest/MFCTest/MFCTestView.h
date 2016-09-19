
// MFCTestView.h : CMFCTestView 类的接口
//

#pragma once
#include "Thread.h"


class CMFCTestView : public CView
{
protected: // 仅从序列化创建
	CMFCTestView();
	DECLARE_DYNCREATE(CMFCTestView)

// 特性
public:
	CMFCTestDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNewThread();
};

#ifndef _DEBUG  // MFCTestView.cpp 中的调试版本
inline CMFCTestDoc* CMFCTestView::GetDocument() const
   { return reinterpret_cast<CMFCTestDoc*>(m_pDocument); }
#endif

