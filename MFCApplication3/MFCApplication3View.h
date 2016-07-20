
// MFCApplication3View.h : CMFCApplication3View ��Ľӿ�
//
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
#include "Animation.h"
#include "PlaneSelf.h"
#include "BulletGeneral.h"
#include "BulletLaser.h"
#include "PlaneEmenyGeneral.h"
#include "Explosion.h"
#include "PlaneBoss.h"
#include "Item.h"
#include "Audio.h"
#include "json.hpp"
#include <string>
#include <fstream>
#include <streambuf>

#pragma once
using namespace Gdiplus;

struct gamesetting {
	int mission_present=0;//��ǰ�ؿ�
	bool bossmode = 0;//bossģʽ
	int mission_level[4] = { 20,50,90,140 };//����ɱ����Ҫ��
	int bossid [4] = {16,17,18,19};//bossid
	int mission_killed = 0;//��ɱ��ͨ�л���Ŀ
	int cooldown_plane_generate[2] = {0,2000};//��һֵΪ״̬�����ڶ���ֵΪĿ����

	int option_infinite_life = 0;
	int option_infinite_laser = 0;
	int option_infinite_missle = 0;



};

class CMFCApplication3View : public CView
{
public:
	Audio mAudio;
public:

	int key_space = 0;//1
public:
	
	void LoadImageFromFile();
	void InitializeItem();
	void InitalizeAirplane();
	void InitializeEquation();

	void CreateExplosion(CPoint pos,int type);
	void DestroyFinishedObject(CObList *a);
	void RemoveLaserBullet();
	void DrawObject(CObList *a);
	void CheckOption() {
		if (mgamesetting.option_infinite_laser)plane_self.mcooldown.fire_laser = 1000;
		if (mgamesetting.option_infinite_missle)plane_self.mcooldown.fire_trace = 1000;
		if (mgamesetting.option_infinite_life)plane_self.mcooldown.protection=1000;
	
	}
	void DestroyAllObject(CObList *a) {
		for (POSITION pos = a->GetHeadPosition(); pos != NULL;)//�ҷ��ӵ���ײ����
		{
			POSITION del = pos;
			FlyingObject *temp = (FlyingObject *)a->GetNext(pos);
			delete temp;
			a->RemoveAt(del);
		}
	}
	void NewGame() {
		StopGame();
		CMFCApplication3Doc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		
		plane_self.setproperty(pDoc->mplane_property[0]);
		plane_self.level = 0;
		plane_self.exp = 3600;

		mgamesetting.mission_killed = 0;
		mgamesetting.bossmode = 0;
		mgamesetting.cooldown_plane_generate[0] = 0;
		mgamesetting.mission_present = 1;

		pDoc->mBackground->setspeed(12);
		pDoc->mBackground->init(1);

		mAudio.PlayBackground();
		this->SetTimer(1, 40, NULL);//draw
		this->SetTimer(4, 40, NULL);//generateenemy
	}
	void StopGame() {
		CMFCApplication3Doc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		mAudio.StopAll();
		this->SetTimer(1, 0, NULL);//draw
		this->SetTimer(4, 0, NULL);//generateenemy
		DestroyAllObject(&pDoc->list_bullet_general_self);//�����ҷ���ͨ�ӵ�
		DestroyAllObject(&pDoc->list_bullet_laser_self);//�����ҷ������ӵ�
		DestroyAllObject(&pDoc->list_bullet_general_enemy);//���ٵз��ӵ�
		DestroyAllObject(&pDoc->list_airplane_enemy);//���ٵз�ս��
		DestroyAllObject(&pDoc->list_explosion);//���ٱ�ը
		DestroyAllObject(&pDoc->list_item);//��������
		if (mgamesetting.bossmode) {
			delete plane_boss;
			plane_boss = NULL;
		}
	
	}

public:
	PlaneSelf plane_self;
	PlaneBoss *plane_boss=NULL;

protected: // �������л�����
	CMFCApplication3View();
	DECLARE_DYNCREATE(CMFCApplication3View)

	

public:
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR   gdiplusToken;
public://˫����
	CBitmap MemBitmap;//˫����
	CDC MemDC;//˫���桢
	CBrush m_brush;//ˢ����

public:
	//��Ϸ����
	void JudgeFlyingObject();//�жϷ���Ŀ��
	void JudgeSetting();//������
	void FireSetting();//�ӵ��������

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
	afx_msg void OnNewGame();
	afx_msg void OnInfinitelifeOn();
	afx_msg void OnInfinitelifeOff();
	afx_msg void OnInfinitelaserbulletShellexecute();
	afx_msg void OnInfinitelaserbulletOff();
	afx_msg void OnInfinitemissileOn();
	afx_msg void OnInfinitemissileOff();
};

#ifndef _DEBUG  // MFCApplication3View.cpp �еĵ��԰汾
inline CMFCApplication3Doc* CMFCApplication3View::GetDocument() const
   { return reinterpret_cast<CMFCApplication3Doc*>(m_pDocument); }
#endif

