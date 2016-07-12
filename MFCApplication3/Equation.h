#pragma once
#include "stdafx.h"
#include "FlyingObject.h"

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
	

	Equation() {};

	bool isfinished() {
		if (time < equation_now.x.target)return false;
		return true;
	
	};
	void loadequation(move_equation_set a) { 
		equation_set = a;
		integeration_x = integeration_y = 0;
		setindex(0);
	};
	void setindex(int a) {
		if (a >= equation_set.num_equation) assert("Equation.cpp::setindex:out of index");
		index = a;
		equation_now = *equation_set.move_equation[index];

		exprtk::symbol_table<float> symbol_table;
		//symbol_table.clear_variables();
		symbol_table.add_variable("t", time);
		symbol_table.add_variable("v", velociety);
		symbol_table.add_constants();

		//expression_x.release();
		//expression_y.release();
		expression_y.register_symbol_table(symbol_table);
		expression_x.register_symbol_table(symbol_table);
		

		{
			exprtk::parser<float> parser;
			parser.compile(equation_now.y.equation, expression_y); }
		{	exprtk::parser<float> parser;
			parser.compile(equation_now.x.equation, expression_x); }

		time = equation_now.x.base;
	};
	void setvelociety(float a) { velociety = a; };
	void calculate() {
		if (isfinished()) {
			index++;
			if ((index) < equation_set.num_equation) {
				setindex(index);

			}
			if (equation_set.loop != -1&& index>= equation_set.num_equation)setindex(equation_set.loop);
			return;
		}
		integeration_y += expression_y.value()*equation_now.x.increment;
		integeration_x += expression_x.value()*equation_now.x.increment;
		
		double a = expression_y.value();
		time = time +equation_now.x.increment;

		
	};
	CPoint getresult() {
		return CPoint((int)integeration_x, (int)integeration_y) + *offset;
	
	};
	void setoffset(CPoint *a) {
		offset = a;

	};

};