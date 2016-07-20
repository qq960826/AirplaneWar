#include "stdafx.h"
#include "PlaneBase.h"
#include "BulletTrace.h"
void PlaneBase::Draw(CDC *pDC) {
	//this->calculate_location();
	mAnimation->drawimage(pDC, this->pos, mproperty.pictureid, 0);
	draw_hp(pDC);
};
void PlaneBase::fire(CObList *bullet,int id) {
	int num = mproperty.mbullet_set->num_each[id];
	for (int i = 0; i < num; i++) {
		BulletGeneral *mbullet = new BulletGeneral( pos, mproperty.mbullet_set->bullet[id][i]);
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
void PlaneBase::setproperty(plane_property *a) {
	mproperty = *a;
	objectsize.x = mAnimation->slice_picture[mproperty.pictureid][0].right;
	objectsize.y = mAnimation->slice_picture[mproperty.pictureid][0].bottom;
	mattack = mproperty.attack;
	hp = mproperty.hp;
	exp = mproperty.exp;
};
void PlaneBase::draw_hp(CDC *pDC) {
	CPoint size_plane = mAnimation->getimagesize(mproperty.pictureid, 0);
	CPoint size_hp0 = pDoc->manimation_hp->getimagesize(0, 0) - CPoint(0, 8);
	CPoint size_hp1 = pDoc->manimation_hp->getimagesize(1, 0);
	CPoint temp_pos = pos;
	temp_pos.y += size_plane.y;

	size_hp0.x = size_plane.x;
	size_hp1.x = (float)((float)hp / (float)mproperty.hp)*size_plane.x;
	pDoc->manimation_hp->drawimage(pDC, temp_pos, size_hp0, 0, 0);
	pDoc->manimation_hp->drawimage(pDC, temp_pos, size_hp1, 1, 0);


};