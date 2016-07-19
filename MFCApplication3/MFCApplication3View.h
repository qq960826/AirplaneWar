
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
//#pragma comment( lib, "json.lib" )
#include "json.hpp"
#include <string>
#include <fstream>
#include <streambuf>
#include "DSBuffer.h"
#include "DSList.h"
#pragma once
using namespace Gdiplus;

struct gamesetting {
	int mission_present=0;//��ǰ�ؿ�
	bool bossmode = 0;//bossģʽ
	int mission_level[4] = { 5,50,90,140 };//����ɱ����Ҫ��
	int bossid [4] = {16,17,18,19};//bossid
	int mission_killed = 0;//��ɱ��ͨ�л���Ŀ
	int cooldown_plane_generate[2] = {0,2000};//��һֵΪ״̬�����ڶ���ֵΪĿ����



};

class CMFCApplication3View : public CView
{
public:
	int music_explosion_index = 1;
	int music_fire_index = 31;
	int music_pickup_index = 62;
	int music_collision_index = 72;
	int music_enemydie_index = 82;
	int music_laser_index = 87;
	int key_space = 0;//1
public:
	CDSList DSlist1;
	void LoadImageFromFile();
	void InitializeItem();
	void InitalizeAirplane();
	void InitializeEquation();

	void CreateExplosion(CPoint pos,int type) {
		CMFCApplication3Doc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		Explosion *temp_explo;
		temp_explo = new Explosion();
		temp_explo->setAnimation(pDoc->manimation_explosion);
		temp_explo->setpos(pos);
		temp_explo->windowsize = pDoc->windowssize;
		temp_explo->type = type;
		pDoc->list_explosion.AddTail((CObject*)temp_explo);
	
	};
	void DestroyFinishedObject(CObList *a) {

		for (POSITION pos = a->GetHeadPosition(); pos != NULL;)//�ҷ��ӵ���ײ����
		{
			POSITION del = pos;
			FlyingObject *temp = (FlyingObject *)a->GetNext(pos);
			temp->calculate_location();
			if (temp->finished) {
				delete temp;
				a->RemoveAt(del);
				continue;
			}
		}
	
	}
	void RemoveLaserBullet() {
		CMFCApplication3Doc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		for (POSITION pos = pDoc->list_bullet_laser_self.GetHeadPosition(); pos != NULL;)//�����ҷ���ͨ�ӵ�
		{
			POSITION del = pos;
			FlyingObject *temp = (FlyingObject *)pDoc->list_bullet_laser_self.GetNext(pos);
			delete temp;
			pDoc->list_bullet_laser_self.RemoveAt(del);
		}
	}
	void DrawObject(CObList *a) {

		for (POSITION pos = a->GetHeadPosition(); pos != NULL;)//�����ҷ���ͨ�ӵ�
		{
			POSITION del = pos;
			FlyingObject *temp = (FlyingObject *)a->GetNext(pos);
			temp->Draw(&MemDC);
		}
	}
	void AudioExplosion() {
		DSlist1.PlayBuffer(music_fire_index, 0);
		music_fire_index++;
		if (music_fire_index >= 61) {
			music_fire_index = 31;

		}
	}
	void AudioFire() {
		DSlist1.PlayBuffer(music_explosion_index, 0);
		music_explosion_index++;
		if (music_explosion_index >= 31) {
			music_explosion_index = 1;
		}
	}
	void AudioPickup() {
		DSlist1.PlayBuffer(music_pickup_index, 0);
		music_pickup_index++;
		if (music_pickup_index >= 72) {
			music_pickup_index = 62;
		}
	}
	void AudioCollision() {
		DSlist1.PlayBuffer(music_collision_index, 0);
		music_collision_index++;
		if (music_collision_index >= 82) {
			music_collision_index = 72;
		}
	}
	void AudioEnemyDie() {
		DSlist1.PlayBuffer(music_enemydie_index, 0);
		music_enemydie_index++;
		if (music_enemydie_index >= 87) {
			music_enemydie_index = 82;
		}
	}
	void AudioWinBoss() {
		DSlist1.PlayBuffer(61, 0);
	}
	void AudioLaser() {
		DSlist1.PlayBuffer(music_laser_index, 0);
		music_laser_index++;
		if (music_laser_index >= 117) {
			music_laser_index = 87;
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
};

#ifndef _DEBUG  // MFCApplication3View.cpp �еĵ��԰汾
inline CMFCApplication3Doc* CMFCApplication3View::GetDocument() const
   { return reinterpret_cast<CMFCApplication3Doc*>(m_pDocument); }
#endif

