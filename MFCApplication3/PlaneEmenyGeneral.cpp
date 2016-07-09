#include "stdafx.h"
#include "PlaneEmenyGeneral.h"
PlaneEmenyGeneral::PlaneEmenyGeneral() :PlaneBase() {
	setHP(10);
	setAttack(5);
};
void PlaneEmenyGeneral:: Draw(CDC *pDC) {
	this->calculate_location();
	mAnimation->drawimage(pDC, this->pos, 0, shape);


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
void PlaneEmenyGeneral::fire(CObList *bullet) {
	BulletGeneral *mbullet = new BulletGeneral(pos, CPoint(0, 20), 0, 5);

	mbullet->windowsize = pDoc->windowssize;
	mbullet->loadAnimation(pDoc->manimation_bullet);
	mbullet->setrotation(180);
	bullet->AddHead((CObject*)mbullet);
};