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

void PlaneBase::fire(CObList *bullet,int id) {
	int num = mproperty->mbullet_set->num_each[id];
	for (int i = 0; i < num; i++) {
		BulletGeneral *mbullet = new BulletGeneral( pos, mproperty->mbullet_set->bullet[id][i]);
		mbullet->windowsize = pDoc->windowssize;
		mbullet->loadAnimation(pDoc->manimation_bullet);
		bullet->AddHead((CObject*)mbullet);
	}



};
CRect PlaneBase::getlocation() {

	return CRect(pos.x, pos.y, objectsize.x, objectsize.y);
};
bool PlaneBase::isCollsion(CRect a) {

	if (isCollsionWithRect(a)) {
		return true;
	};
	return false;
};