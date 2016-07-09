#pragma once
#include "stdafx.h"
class Animation {
public:
	RECT ** slice_picture;
	int * slice_num;
	Gdiplus::Image** image;
	int image_num = 0;
	float rotation = 0;
	Animation(int num);

	void addimage(Gdiplus::Image *mimage, int *mrec, int num);
	void addimage(Gdiplus::Image *mimage);
	void drawimage(CDC *pDC, CPoint pos, int image_index, int animation_index);
	~Animation() ;
	void setrotation(float angle);
	CPoint getimagesize(int image_index, int animation_index);

};