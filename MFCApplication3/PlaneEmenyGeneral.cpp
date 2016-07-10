#include "stdafx.h"
#include "PlaneEmenyGeneral.h"
PlaneEmenyGeneral::PlaneEmenyGeneral() :PlaneBase() {
	setHP(10);
	setAttack(5);
};
void PlaneEmenyGeneral:: Draw(CDC *pDC) {
	this->calculate_location();
	mAnimation->drawimage(pDC, this->pos, mproperty->pictureid,0);


};
void PlaneEmenyGeneral::setAttack(int a) { mattack = a; };
void PlaneEmenyGeneral::setHP(int b) { hp = b; };
void PlaneEmenyGeneral::Onedgeleft() {

};
void PlaneEmenyGeneral::Onedgetop() {


};
void PlaneEmenyGeneral::Onedgeright() {


};
void PlaneEmenyGeneral::Onedgebottom() {

};
void PlaneEmenyGeneral::fire(CObList *bullet,int id) {
	int num = mproperty->mbullet_set->num_each[id];
	for (int i = 0; i < num; i++) {
		BulletGeneral *mbullet = new BulletGeneral(pos, CPoint(0, 20), mproperty->mbullet_set->bullet[id][i]);
		mbullet->windowsize = pDoc->windowssize;
		mbullet->loadAnimation(pDoc->manimation_bullet);
		bullet->AddHead((CObject*)mbullet);
	}
	


	//mbullet->setrotation(180);
	
};