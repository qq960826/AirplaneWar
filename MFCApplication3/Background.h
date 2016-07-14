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
	void setscreensize(CPoint a);
	void setspeed(int a);
	void init(int index);
	void drawbackground(CDC *Pdc);

};