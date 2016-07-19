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
		int fire_trace=0;//����ʱ��
		int fire_laser=0;//����ʱ��
		int protection=0;//����ʱ��

	} mcooldown;

	int cooldown_laser=0;//���Ƽ��ʹ��

	int level;
	
	PlaneSelf() :PlaneBase() {};
	void Onedgeleft() ;
	void Onedgetop();
	void Onedgeright();
	void Onedgebottom();
	void fire_trace(CObList *bullet, FlyingObject *target);
	void fire_laser(CObList *bullet);
	void calculate_cooldown();
	void getitem(Item item);
};