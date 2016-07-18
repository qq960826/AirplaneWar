#include "stdafx.h"
#include "PlaneBase.h"
#include "FlyingObject.h"
#include "BulletTrace.h"
#include "BulletLaser.h"
#include "Item.h"
#pragma once
class PlaneSelf :public PlaneBase {
public:
	struct cooldown {
		int fire_general=0;
		int fire_trace=0;//发射时间
		int fire_laser=0;//发射时间
		int protection=0;//保护时间

	} mcooldown;

	int level;
	
	PlaneSelf() :PlaneBase() {};
	void Onedgeleft() ;
	void Onedgetop();
	void Onedgeright();
	void Onedgebottom();
	void fire_trace(CObList *bullet, FlyingObject *target) {
		if (mcooldown.fire_trace<=0)return;
		int num = mproperty->mbullet_set->num_each[1];
		for (int i = 0; i < num; i++) {
			BulletTrace  *mbullet = new BulletTrace(pos, mproperty->mbullet_set->bullet[1][i]);
			mbullet->loadAnimation(pDoc->manimation_bullet);
			mbullet->windowsize = pDoc->windowssize;
			mbullet->settarget(target);
			bullet->AddHead((CObject*)mbullet);
		}
	}
	void fire_laser(CObList *bullet) {
		if (mcooldown.fire_laser <= 100) { 
			mcooldown.fire_laser += 100;
			return; }
		mcooldown.fire_laser = 0;

		int num = mproperty->mbullet_set->num_each[1];

			BulletLaser  *mbullet = new BulletLaser();
			mbullet->setgunman(this);
			mbullet->setproperty(mproperty->mbullet_set->bullet[2][0]);

			mbullet->loadAnimation(pDoc->manimation_bullet);
			
			mbullet->windowsize = pDoc->windowssize;
			bullet->AddHead((CObject*)mbullet);

	}
	void calculate_cooldown() {
		if (mcooldown.protection > 0) {
			mcooldown.protection -= 100;
		}
		if (mcooldown.fire_trace > 0) {
			mcooldown.fire_trace -= 100;
		}
	}
	void getitem(Item item) {
		switch (item.property.type) {
		case 0://hp
			hp += item.property.value;
			if (hp > mproperty->hp) {
				hp = mproperty->hp;
			}
			break;
		case 1://protection
			mcooldown.protection = item.property.value;
			break;
		case 2://laser bullet
			mcooldown.fire_trace += item.property.value;
			break;
		case 3://trace bullet
			mcooldown.fire_laser += item.property.value;
			break;
		
		}
	
	}
};