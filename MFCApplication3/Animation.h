#pragma once
#include "stdafx.h"
class Animation {
public:
	RECT ** slice_picture;
	int * slice_num;
	Gdiplus::Image** image;
	float scale=1;
	int image_num = 0;
	float rotation = 0;
	Animation(int num);
	void addimage(Gdiplus::Image *mimage, int *mrec, int num);
	void addimage(Gdiplus::Image *mimage);
	void drawimage(CDC *pDC, CPoint pos, int image_index, int animation_index);
	~Animation() ;
	void setrotation(float angle);
	void setscale(float a) { scale = a; };
	CPoint getimagesize(int image_index, int animation_index);
	CPoint getsize(int image_index, int animation_index);
	void drawimage(CDC *pDC, CPoint pos, CPoint size, int image_index, int animation_index);
};