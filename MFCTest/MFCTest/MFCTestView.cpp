
// MFCTestView.cpp : CMFCTestView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCTest.h"
#endif

#include "MFCTestDoc.h"
#include "MFCTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCTestView

IMPLEMENT_DYNCREATE(CMFCTestView, CView)

BEGIN_MESSAGE_MAP(CMFCTestView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_NEW_THREAD, &CMFCTestView::OnNewThread)
END_MESSAGE_MAP()

// CMFCTestView 构造/析构

CMFCTestView::CMFCTestView()
{
	// TODO: 在此处添加构造代码

}

CMFCTestView::~CMFCTestView()
{
}

BOOL CMFCTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCTestView 绘制

void CMFCTestView::OnDraw(CDC* /*pDC*/)
{
	CMFCTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCTestView 打印

BOOL CMFCTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCTestView 诊断

#ifdef _DEBUG
void CMFCTestView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCTestDoc* CMFCTestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCTestDoc)));
	return (CMFCTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCTestView 消息处理程序


void CMFCTestView::OnNewThread()
{
	// TODO: 在此添加命令处理程序代码
	AfxBeginThread(RUNTIME_CLASS(CThread));
}
