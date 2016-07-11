#pragma once
#include "PlaneBase.h"
class PlaneEmenyGeneral:public PlaneBase {
public:
	int cooldown_collision ;
	PlaneEmenyGeneral();
	void setAttack(int) ;
	void setHP(int);
	void Onedgeleft() ;
	void Onedgetop() ;
	void Onedgeright();
	void Onedgebottom();
	//void fire(CObList *bullet,int id);


};