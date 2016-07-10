
// MFCApplication3Doc.h : CMFCApplication3Doc ��Ľӿ�
//

#include "stdafx.h"
#include "Background.h"

#pragma once


class CMFCApplication3Doc : public CDocument
{

public://ͼƬ��Դ

	Animation *manimation_airplane_self;
	Animation *manimation_enemy;
	Animation *manimation_background;
	Animation *manimation_animation;
	Animation *manimation_bullet;

	Background *mBackground;


	struct plane_property **mplane_property;


	//Gdiplus::Image *image_bullet_general;

public:
	CPoint *windowssize;
public://DoubleLinkedList
	CObList list_bullet_general_self;
	CObList list_bullet_general_enemy;
	CObList list_airplane_enemy;
	CObList list_explosion;

protected: // �������л�����
	CMFCApplication3Doc();
	DECLARE_DYNCREATE(CMFCApplication3Doc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMFCApplication3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ�����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};