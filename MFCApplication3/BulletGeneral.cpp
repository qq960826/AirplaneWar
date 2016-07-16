#include "stdafx.h"
#include "BulletGeneral.h";
void BulletGeneral::loadAnimation(Animation *a) {
	mAnimation = a;
	objectsize.x = mAnimation->slice_picture[property->pictureid][0].right;
	objectsize.y = mAnimation->slice_picture[property->pictureid][0].bottom;
	pos = pos + *property->offset;
};
void BulletGeneral:: Draw(CDC *pDoc) {
	//calculate_location();
	mAnimation->setrotation(roataion);
	mAnimation->setscale(property->scale);
	mAnimation->drawimage(pDoc, pos, property->pictureid, 0);


};