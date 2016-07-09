#include "stdafx.h"
#include "BulletGeneral.h";
void BulletGeneral::loadAnimation(Animation *a) {
	mAnimation = a;

};
void BulletGeneral:: Draw(CDC *pDoc) {
	calculate_location();
	mAnimation->drawimage(pDoc, pos, type, 0);
};