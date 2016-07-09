#include "stdafx.h"
#include "PlaneBase.h"

void PlaneBase::draw(CDC *pDC){
	
	this->calculate_location();
	if (this->velocity.x < 0) {
		objectsize = mAnimation->getimagesize(0, 0);
		mAnimation->drawimage(pDC, this->pos, 0, 0);
	}
	else if (this->velocity.x == 0) {
		objectsize = mAnimation->getimagesize(0, 2);
		mAnimation->drawimage(pDC, this->pos, 0, 2);
	}
	else if (this->velocity.x> 0) {
		objectsize = mAnimation->getimagesize(0, 4);
		mAnimation->drawimage(pDC, this->pos, 0, 4);
	}

};

void PlaneBase::fire(CObList *bullet) {
	BulletGeneral *mbullet = new BulletGeneral(pos, CPoint(0, -10), 0, 5);
	int b[] = { 629,531,36,85 };
	mbullet->mAnimation = pDoc->manimation_bullet;
	mbullet->windowsize = pDoc->windowssize;
	//mbullet->mAnimation->addimage(pDoc->image_bullet_general, b, 5);
	mbullet->setattack(5);
	mbullet->settype(12);
	bullet->AddHead((CObject*)mbullet);
};
CRect PlaneBase::getlocation() {
	objectsize.x = mAnimation->slice_picture[0][shape].right;
	objectsize.y = mAnimation->slice_picture[0][shape].bottom;
	return CRect(pos.x, pos.y, objectsize.x, objectsize.y);
};
bool PlaneBase::isCollsion(CRect a) {

	if (isCollsionWithRect(a)) {
		return true;
	};
	return false;
};