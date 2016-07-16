#include "stdafx.h"
#include "PlaneBase.h"
#include "FlyingObject.h"
#include "BulletTrace.h"
#pragma once
class PlaneSelf :public PlaneBase {
public:
	int level;
	
	PlaneSelf() :PlaneBase() {};
	void Onedgeleft() ;
	void Onedgetop();
	void Onedgeright();
	void Onedgebottom();
	void fire_trace(CObList *bullet, FlyingObject *target) {
		BulletTrace  *mbullet = new BulletTrace(pos, mproperty->mbullet_set->bullet[0][0]);
		mbullet->loadAnimation(pDoc->manimation_bullet);
		mbullet->windowsize = pDoc->windowssize;
		mbullet->settarget(target);
		bullet->AddHead((CObject*)mbullet);
		//mbullet->loadAnimation(pdoc->manimation_bullet);

		//bullet->addhead((cobject*)mbullet);
	}
	
};