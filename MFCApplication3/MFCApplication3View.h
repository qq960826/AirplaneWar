
// MFCApplication3View.h : CMFCApplication3View ��Ľӿ�
//
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
#include "Animation.h"
#include "PlaneSelf.h"
#include "BulletGeneral.h"
#include "PlaneEmenyGeneral.h"
#include "Explosion.h"
#include "PlaneBoss.h"
//#pragma comment( lib, "json.lib" )
#include "json.hpp"
#include <string>
#include <fstream>
#include <streambuf>
#pragma once
using namespace Gdiplus;

struct gamesetting {
	int mission_present=0;//��ǰ�ؿ�
	bool bossmode = 0;//bossģʽ
	int mission_level[4] = { 5,50,90,140 };//����ɱ����Ҫ��
	int bossid [4] = {16,17,18,19};//bossid
	int mission_killed = 0;//��ɱ��ͨ�л���Ŀ
	



};

class CMFCApplication3View : public CView
{
public:
	void InitalizeAirplane();
	void InitializeEquation();
public:
	PlaneSelf plane_self;
	PlaneBoss *plane_boss=NULL;

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

public:
	gamesetting mgamesetting;
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

