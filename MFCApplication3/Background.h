#pragma once
#include "Animation.h"
#include "stdafx.h"
class Background {
private:
	int speed;
	int index;
	CPoint screensize;
	int y1, y2;
public:
	Animation *mAnimation;
	Background() {};
	void init(int index);
	void setscreensize(CPoint a);
	void setspeed(int a);
	void drawbackground(CDC *Pdc);
	void drawproperty(CDC *Pdc);

};