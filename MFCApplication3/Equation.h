#pragma once
#include "stdafx.h"
#include "FlyingObject.h"

#include "exprtk.hpp"
class Equation {//对参数方程进行
public:
	move_equation_set equation_set;
	move_equation equation_now;

	CPoint *offset;

	int index;

	float time;
	float velociety;

	float integeration_x;
	float integeration_y;

	
	exprtk::expression<float> expression_x;
	exprtk::expression<float> expression_y;
	

	Equation() ;
	void loadequation(move_equation_set a) ;
	void setindex(int a);
	void setvelociety(float a);
	void setoffset(CPoint *a);
	CPoint getresult();
	void calculate();
	bool isfinished();

};