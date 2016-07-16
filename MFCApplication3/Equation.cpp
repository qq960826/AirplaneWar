#include "Equation.h"
Equation::Equation() {};

bool Equation::isfinished() {
	if (time < equation_now.x.target)return false;
	return true;

};
void Equation::loadequation(move_equation_set a) {
	equation_set = a;
	integeration_x = integeration_y = 0;
	setindex(0);
};
void Equation::setindex(int a) {
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
void Equation::setvelociety(float a) { velociety = a; };
void Equation::calculate() {
	if (isfinished()) {
		index++;
		if ((index) < equation_set.num_equation) {
			setindex(index);

		}
		if (equation_set.loop != -1 && index >= equation_set.num_equation)setindex(equation_set.loop);
		return;
	}
	integeration_y += expression_y.value()*equation_now.x.increment;
	integeration_x += expression_x.value()*equation_now.x.increment;

	double a = expression_y.value();
	time = time + equation_now.x.increment;


};
CPoint Equation::getresult() {
	return CPoint((int)integeration_x, (int)integeration_y) + *offset;

};
void Equation::setoffset(CPoint *a) {
	offset = a;

};