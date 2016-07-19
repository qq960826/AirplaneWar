#pragma once
#include "BulletGeneral.h"
#include "PlaneBase.h"
class BulletLaser:public BulletGeneral {
public:
	//bullet_property *property;
	PlaneBase *gunman;
	CPoint offset;
	CPoint integration;
	BulletLaser() ;
	void setgunman(PlaneBase *a) ;
	void calculate_location();
	void loadAnimation(Animation *a);
	void setproperty(bullet_property *a);
};