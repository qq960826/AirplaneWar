#pragma once
#include "stdafx.h"
#include "BulletGeneral.h"
#include "FlyingObject.h"
class BulletTrace :public BulletGeneral {
public:
	int stoptrack;
	FlyingObject *target;
	BulletTrace(CPoint mpos, bullet_property *mproperty);
	void settarget(FlyingObject *a);
	void calculate_trace();
	void calculate_location();
};