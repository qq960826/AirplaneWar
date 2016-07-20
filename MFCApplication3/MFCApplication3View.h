
// MFCApplication3View.h : CMFCApplication3View 类的接口
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
	int mission_present=0;//当前关卡
	bool bossmode = 0;//boss模式
	int mission_level[4] = { 20,50,90,140 };//升级杀敌数要求
	int bossid [4] = {16,17,18,19};//bossid
	int mission_killed = 0;//已杀普通敌机数目
	int cooldown_plane_generate[2] = {0,2000};//第一值为状态量，第二个值为目标量

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
		for (POSITION pos = a->GetHeadPosition(); pos != NULL;)//我发子弹碰撞销毁
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
		DestroyAllObject(&pDoc->list_bullet_general_self);//销毁我方普通子弹
		DestroyAllObject(&pDoc->list_bullet_laser_self);//销毁我方激光子弹
		DestroyAllObject(&pDoc->list_bullet_general_enemy);//销毁敌方子弹
		DestroyAllObject(&pDoc->list_airplane_enemy);//销毁敌方战机
		DestroyAllObject(&pDoc->list_explosion);//销毁爆炸
		DestroyAllObject(&pDoc->list_item);//销毁物资
		if (mgamesetting.bossmode) {
			delete plane_boss;
			plane_boss = NULL;
		}
	
	}

public:
	PlaneSelf plane_self;
	PlaneBoss *plane_boss=NULL;

protected: // 仅从序列化创建
	CMFCApplication3View();
	DECLARE_DYNCREATE(CMFCApplication3View)

	

public:
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR   gdiplusToken;
public://双缓冲
	CBitmap MemBitmap;//双缓存
	CDC MemDC;//双缓存、
	CBrush m_brush;//刷背景

public:
	//游戏控制
	void JudgeFlyingObject();//判断飞行目标
	void JudgeSetting();//剧情检测
	void FireSetting();//子弹发射剧情

public:
	gamesetting mgamesetting;
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
	afx_msg void OnNewGame();
	afx_msg void OnInfinitelifeOn();
	afx_msg void OnInfinitelifeOff();
	afx_msg void OnInfinitelaserbulletShellexecute();
	afx_msg void OnInfinitelaserbulletOff();
	afx_msg void OnInfinitemissileOn();
	afx_msg void OnInfinitemissileOff();
};

#ifndef _DEBUG  // MFCApplication3View.cpp 中的调试版本
inline CMFCApplication3Doc* CMFCApplication3View::GetDocument() const
   { return reinterpret_cast<CMFCApplication3Doc*>(m_pDocument); }
#endif

