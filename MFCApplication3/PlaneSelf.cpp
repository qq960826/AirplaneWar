#include "stdafx.h"
#include "PlaneSelf.h"
void PlaneSelf::Onedgeleft() {
	pos.x = 0;
	if (velocity.x < 0)velocity.x = 0;
};
void PlaneSelf::Onedgetop() {
	pos.y = 0;
	velocity.y = 0;

};
void PlaneSelf::Onedgeright() {
	pos.x = windowsize->x - objectsize.x;
	if (velocity.x> 0)velocity.x = 0;

};
void PlaneSelf::Onedgebottom() {
	pos.y = windowsize->y - objectsize.y;
	if (velocity.y < 0)velocity.y = 0;
};

void PlaneSelf::fire_trace(CObList *bullet, FlyingObject *target) {
	if (mcooldown.fire_trace <= 0)return;
	int num = mproperty.mbullet_set->num_each[1];
	for (int i = 0; i < num; i++) {
		BulletTrace  *mbullet = new BulletTrace(pos, mproperty.mbullet_set->bullet[1][i]);
		mbullet->loadAnimation(pDoc->manimation_bullet);
		mbullet->windowsize = pDoc->windowssize;
		mbullet->settarget(target);
		bullet->AddHead((CObject*)mbullet);
	}
};
void PlaneSelf::fire_laser(CObList *bullet) {
	//mcooldown.fire_laser = 100;
	if (mcooldown.fire_laser <= 0)return;
	if (cooldown_laser <= 200) {
		cooldown_laser += 50;
		return;
	}
	cooldown_laser = 0;

	int num = mproperty.mbullet_set->num_each[2];
	for (int i = 0; i < num; i++) {
		BulletLaser  *mbullet = new BulletLaser();
		mbullet->setproperty(mproperty.mbullet_set->bullet[2][i]);
		mbullet->setgunman(this);
		mbullet->loadAnimation(pDoc->manimation_bullet);
		mbullet->windowsize = pDoc->windowssize;
		bullet->AddHead((CObject*)mbullet);
	}
};
void PlaneSelf::calculate_cooldown() {
	if (mcooldown.protection > 0) {
		mcooldown.protection -= 50;
	}
	if (mcooldown.fire_trace > 0) {
		mcooldown.fire_trace -= 50;
	}
	if (mcooldown.fire_laser > 0) {
		mcooldown.fire_laser -= 50;
	}
};
void PlaneSelf::getitem(Item item) {
	switch (item.property.type) {
	case 0://hp
		hp += item.property.value;
		if (hp > mproperty.hp) {
			hp = mproperty.hp;
		}
		break;
	case 1://protection
		mcooldown.protection += item.property.value;
		break;
	case 2://trace bullet
		mcooldown.fire_trace += item.property.value;
		break;
	case 3://laser bullet
		mcooldown.fire_laser += item.property.value;
		break;

	}

};