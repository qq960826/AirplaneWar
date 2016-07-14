#pragma once
#include "PlaneBase.h"
#include "Equation.h"

class PlaneEmenyGeneral:public PlaneBase {
public:
	move_equation_set equation_set;
	Equation mequation;
	CPoint offset;

	int cooldown_collision ;
	PlaneEmenyGeneral();
	void setAttack(int) ;
	void setHP(int);
	void Onedgeleft() ;
	void Onedgetop() ;
	void Onedgeright();
	void Onedgebottom();
	void setequation(move_equation_set *a) {
		equation_set = *a;
		mequation.loadequation(equation_set);
		mequation.setoffset(&equation_set.offset);
	};
	void setoffset(CPoint a) {
		offset = a;
	};
	void calculate_location() {
		mequation.calculate();
		pos = mequation.getresult();
		edgedetect();
		
	
	};
	void setvelociety(float a) { mequation.setvelociety(a); }
	

};