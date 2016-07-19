#pragma once
#include "PlaneBase.h"
#include "Equation.h"

class PlaneEmenyGeneral:public PlaneBase {
public:
	move_equation_set equation_set;
	Equation mequation;
	CPoint offset;

	PlaneEmenyGeneral();
	void setAttack(int) ;
	void setHP(int);
	void Onedgeleft() ;
	void Onedgetop() ;
	void Onedgeright();
	void Onedgebottom();
	void setequation(move_equation_set *a);
	void setoffset(CPoint a);
	void calculate_location();
	void setvelociety(float a);
	

};