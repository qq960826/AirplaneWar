#include "stdafx.h"
#include "PlaneBase.h"
#pragma once
class PlaneSelf :public PlaneBase {
protected:
	
public:
	int level;
	PlaneSelf() :PlaneBase() {};
	void Onedgeleft() ;
	void Onedgetop();
	void Onedgeright();
	void Onedgebottom();
	void draw(CDC *pDC);
};
