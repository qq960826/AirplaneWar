#pragma once
#include "stdafx.h"
#include "FlyingObject.h"
#include "BulletGeneral.h"
class PlaneBase:public FlyingObject {

public :
	int exp;
	plane_property *mproperty;
	PlaneBase() :FlyingObject() {};
	void draw(CDC *);
	void fire(CObList *bullet,int bulletid);
	CRect getlocation();
	bool isCollsion(CRect a);
	void setproperty(plane_property *a) {
		mproperty = a;
		objectsize.x = mAnimation->slice_picture[mproperty->pictureid][0].right;
		objectsize.y = mAnimation->slice_picture[mproperty->pictureid][0].bottom;
		mattack = mproperty->attack;
		hp = mproperty->hp;
		exp=mproperty->exp;
	}
	void draw_hp(CDC *pDC) {
		CPoint size_plane = mAnimation->getimagesize(mproperty->pictureid, 0);
		CPoint size_hp0 = pDoc->manimation_hp->getimagesize(0, 0)-CPoint(0,8);
		CPoint size_hp1 = pDoc->manimation_hp->getimagesize(1, 0);
		CPoint temp_pos = pos;
		temp_pos.y += size_plane.y;

		size_hp0.x = size_plane.x;
		size_hp1.x = (float)((float)hp / (float)mproperty->hp)*size_plane.x;
		pDoc->manimation_hp->drawimage(pDC, temp_pos, size_hp0, 0, 0);
		pDoc->manimation_hp->drawimage(pDC, temp_pos, size_hp1, 1, 0);
	
	
	};
};