#include "stdafx.h"
#include "PlaneEmenyGeneral.h"
PlaneEmenyGeneral::PlaneEmenyGeneral() :PlaneBase() {
	cooldown_collision = 0;


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