
#include "stdafx.h"
#include "Background.h"
void Background::setscreensize(CPoint a) {
	screensize = a;
};
void Background::setspeed(int a) {
	speed = a;
};
void Background::init(int index) {
	int size_y = mAnimation->image[index]->GetHeight();
	y1 =0 ;
	y2 = -size_y;
};
void Background::drawbackground(CDC *Pdc, int index) {
	int size_y = mAnimation->image[index]->GetHeight();
	y1 += speed;
	y2 += speed;
	if (y2 > screensize.y) {
		y2 = y1 - size_y ;
		//y1 = 0;
	}
	if (y1 > screensize.y) {
		y1 = y2 - size_y;
		//y2 = 0;
	}
	mAnimation->drawimage(Pdc, CPoint(0, y1), index, 0);
	mAnimation->drawimage(Pdc, CPoint(0, y2), index, 0);

};