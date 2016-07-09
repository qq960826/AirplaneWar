#pragma once
#include "PlaneBase.h"
class PlaneEmenyGeneral:public PlaneBase {
public:
	PlaneEmenyGeneral();
	void setAttack(int) ;
	void setHP(int);
	void Draw(CDC *pDC) ;
	void Onedgeleft() ;
	void Onedgetop() ;
	void Onedgeright();
	void Onedgebottom();
	void fire(CObList *bullet);


};