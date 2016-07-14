#include "stdafx.h"
#include "PlaneEmenyGeneral.h"
PlaneEmenyGeneral::PlaneEmenyGeneral() :PlaneBase() {
	cooldown_collision = 0;
	cooldown_fire = 0;


};
void PlaneEmenyGeneral::setAttack(int a) { mattack = a; };
void PlaneEmenyGeneral::setHP(int b) { hp = b; };
void PlaneEmenyGeneral::Onedgeleft() {
	if (pos.x<-objectsize.x)finished = 1;
};
void PlaneEmenyGeneral::Onedgetop() {
	if (pos.y<-objectsize.x)finished = 1;

};
void PlaneEmenyGeneral::Onedgeright() {
	if (pos.x>objectsize.x + windowsize->x)finished = 1;

};
void PlaneEmenyGeneral::Onedgebottom() {
	if (pos.y>objectsize.y + windowsize->y)finished = 1;
};
//void PlaneEmenyGeneral::fire(CObList *bullet,int id) {
//	int num = mproperty->mbullet_set->num_each[id];
//	for (int i = 0; i < num; i++) {
//		
//		BulletGeneral *mbullet = new BulletGeneral(pos, mproperty->mbullet_set->bullet[id][i]);
//		mbullet->windowsize = pDoc->windowssize;
//		mbullet->loadAnimation(pDoc->manimation_bullet);
//		bullet->AddHead((CObject*)mbullet);
//	}
//	
//
//
//	//mbullet->setrotation(180);
//	
//};