
// MFCApplication3View.h : CMFCApplication3View ��Ľӿ�
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

protected: // �������л�����
	CMFCApplication3View();
	DECLARE_DYNCREATE(CMFCApplication3View)

public:
	void LoadImageFromFile();

public:
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR   gdiplusToken;
public://˫����
	CBitmap MemBitmap;//˫����
	CDC MemDC;//˫���桢
	CBrush m_brush;//ˢ����
// ����
public:
	CMFCApplication3Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMFCApplication3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // MFCApplication3View.cpp �еĵ��԰汾
inline CMFCApplication3Doc* CMFCApplication3View::GetDocument() const
   { return reinterpret_cast<CMFCApplication3Doc*>(m_pDocument); }
#endif

