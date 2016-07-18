
// MFCApplication3Doc.h : CMFCApplication3Doc 类的接口
//

#include "stdafx.h"
#include "Background.h"

#pragma once


class CMFCApplication3Doc : public CDocument
{

public://图片资源

	Animation *manimation_airplane_self;
	Animation *manimation_enemy;
	Animation *manimation_background;
	Animation *manimation_explosion;
	Animation *manimation_bullet;
	Animation *manimation_hp;
	Animation *manimation_item;


	Background *mBackground;


	struct plane_property **mplane_property;//飞机参数
	struct move_equation_set **mmove_equation_set;//轨迹方程
	struct item_properity **mitem_properity;//物资类




	//Gdiplus::Image *image_bullet_general;

public:
	CPoint *windowssize;
public://DoubleLinkedList
	CObList list_bullet_general_self;
	CObList list_bullet_general_enemy;
	CObList list_bullet_laser_self;
	CObList list_airplane_enemy;
	CObList list_explosion;
	CObList list_item;//物资类
protected: // 仅从序列化创建
	CMFCApplication3Doc();
	DECLARE_DYNCREATE(CMFCApplication3Doc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMFCApplication3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
