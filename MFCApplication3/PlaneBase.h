#pragma once
#include "stdafx.h"
#include "FlyingObject.h"
#include "BulletGeneral.h"

class PlaneBase:public FlyingObject {
protected:
	
	
	
public :
 
	plane_property *mproperty;
	PlaneBase() :FlyingObject() {};
	void draw(CDC *);
	void fire(CObList *bullet,int bulletid);
	CRect getlocation();
	bool isCollsion(CRect a);
	void setproperty(plane_property *a) {
		mproperty = a;
	}
	
};