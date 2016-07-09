
// MFCApplication3View.h : CMFCApplication3View 类的接口
//
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
#include "Animation.h"
#include "PlaneSelf.h"
#include "BulletGeneral.h"
#include "PlaneEmenyGeneral.h"
#include "Explosion.h"
//#pragma comment( lib, "json.lib" )
#include "json.hpp"

#pragma once
using namespace Gdiplus;



class CMFCApplication3View : public CView
{
public:
	void InitalizeAirplane();
public:
	PlaneSelf plane_self;

protected: // 仅从序列化创建
	CMFCApplication3View();
	DECLARE_DYNCREATE(CMFCApplication3View)

public:
	void LoadImageFromFile();

public:
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR   gdiplusToken;
public://双缓冲
	CBitmap MemBitmap;//双缓存
	CDC MemDC;//双缓存、
	CBrush m_brush;//刷背景
// 特性
public:
	CMFCApplication3Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCApplication3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // MFCApplication3View.cpp 中的调试版本
inline CMFCApplication3Doc* CMFCApplication3View::GetDocument() const
   { return reinterpret_cast<CMFCApplication3Doc*>(m_pDocument); }
#endif

