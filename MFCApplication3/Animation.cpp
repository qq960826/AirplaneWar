#include "stdafx.h"
#include "Animation.h"

Animation::Animation(int num) {
	slice_picture = new  RECT *[num];
	slice_num = new int[num];
	image = new Gdiplus::Image *[num];
	//image_num = num;

};
void Animation::addimage(Gdiplus::Image *mimage, int *mrec, int num) {
	RECT* temp_slice = new RECT[num];
	for (int i = 0; i < num; i++) {
		temp_slice[i].left = mrec[i * 4 + 0];
		temp_slice[i].top = mrec[i * 4 + 1];
		temp_slice[i].right = mrec[i * 4 + 2];
		temp_slice[i].bottom = mrec[i * 4 + 3];
	}
	slice_picture[image_num] = temp_slice;
	slice_num[image_num] = num;
	image[image_num] = mimage;
	image_num++;
};
void Animation::addimage(Gdiplus::Image *mimage) {
	RECT* temp_slice = new RECT[1];
	int i = 0;

	temp_slice[i].left = 0;
	temp_slice[i].top = 0;
	temp_slice[i].right = mimage->GetWidth();
	temp_slice[i].bottom = mimage->GetHeight();

	slice_picture[image_num] = temp_slice;
	slice_num[image_num] = 1;
	image[image_num] = mimage;
	image_num++;
};
void Animation::drawimage(CDC *pDC, CPoint pos, int image_index, int animation_index) {
	Gdiplus::Graphics graphics(pDC->m_hDC);

	float moveX = slice_picture[image_index][animation_index].right / 2 + pos.x;
	float moveY = slice_picture[image_index][animation_index].bottom / 2 + pos.y;
	graphics.TranslateTransform(moveX, moveY);
	graphics.RotateTransform(rotation, Gdiplus::MatrixOrderPrepend);
	graphics.TranslateTransform(-moveX, -moveY);



	//Gdiplus::Pen blackPen(Gdiplus::Color(255, 0, 0, 0), 3);
	//graphics.DrawRectangle(&blackPen, pos.x, pos.y
	//	, slice_picture[image_index][animation_index].right, slice_picture[image_index][animation_index].bottom);
	Gdiplus::ImageAttributes attrs;
	//attrs.SetWrapMode(Gdiplus::WrapModeTileFlipXY);
	graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHalf);
	Gdiplus::Rect  rect = Gdiplus::Rect(pos.x, pos.y, slice_picture[image_index][animation_index].right, slice_picture[image_index][animation_index].bottom);
	graphics.DrawImage(image[image_index], rect, slice_picture[image_index][animation_index].left, slice_picture[image_index][animation_index].top
		, slice_picture[image_index][animation_index].right, slice_picture[image_index][animation_index].bottom, Gdiplus::UnitPixel,&attrs,NULL,NULL);
	};

Animation::~Animation() {
	delete[]slice_picture;
	delete slice_num;
	delete image;
};
void  Animation::setrotation(float angle) { rotation = angle; }
CPoint  Animation::getimagesize(int image_index, int animation_index) { return CPoint(slice_picture[image_index][animation_index].right, slice_picture[image_index][animation_index].bottom); }
