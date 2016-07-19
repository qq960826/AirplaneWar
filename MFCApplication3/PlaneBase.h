#pragma once
#include "stdafx.h"
#include "FlyingObject.h"
#include "BulletGeneral.h"
class PlaneBase:public FlyingObject {

public :
	int exp;
	int cooldown_fire[10] = {0};
	int cooldown_collision;
	plane_property *mproperty;
	PlaneBase() :FlyingObject() {};
	void Draw(CDC *);
	void fire(CObList *bullet,int bulletid);
	CRect getlocation();
	bool isCollsion(CRect a);
	void setproperty(plane_property *a);
	void draw_hp(CDC *pDC);
};