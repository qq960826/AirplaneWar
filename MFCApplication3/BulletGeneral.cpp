#include "stdafx.h"
#include "BulletGeneral.h";
void BulletGeneral::loadAnimation(Animation *a) {
	mAnimation = a;
	objectsize.x = mAnimation->slice_picture[property->pictureid][0].right;
	objectsize.y = mAnimation->slice_picture[property->pictureid][0].bottom;

};
void BulletGeneral:: Draw(CDC *pDoc) {
	calculate_location();

	mAnimation->drawimage(pDoc, pos+*property->offset, property->pictureid, 0);

};