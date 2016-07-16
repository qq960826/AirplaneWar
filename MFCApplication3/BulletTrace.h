#pragma once
#include "BulletGeneral.h"
#include "FlyingObject.h"
class BulletTrace :public BulletGeneral {
public:
	int stoptrack;
	FlyingObject *target;
	BulletTrace(CPoint mpos, bullet_property *mproperty) :BulletGeneral(mpos, mproperty) {};
	void settarget(FlyingObject *a) {
		target = a;
	}
	void calculate_trace() {
		if (stoptrack)return;
		if (target==NULL) {
			stoptrack = 1;
			return;
		}
		if (target->finished == 1) {
			stoptrack = 1;
			return;
		}
		CPoint delta = target->pos- pos;
		CPoint temp_velocity;
		if (delta.x == 0) {
			if (delta.y > 0) {
				temp_velocity.y = speed;
				temp_velocity.x = 0;
			}
			else {
				temp_velocity.y = -speed;
				temp_velocity.x = 0;
			}

				return;
		}
		float temp1 = atan((float)delta.y/ (float)delta.x)*180/pi1;
		//roataion =360- temp1;
		if (delta.x > 0) {
			temp_velocity.x = -speed*cos((temp1*pi1) / 180);
			temp_velocity.y = -speed*sin((temp1*pi1) / 180);
			velocity = temp_velocity;
			//::PlaySound(L"hello.wav", NULL, SND_FILENAME);
		}
		else {
			temp_velocity.x = speed*cos((temp1*pi1) / 180);
			temp_velocity.y = speed*sin((temp1*pi1) / 180);
			velocity = temp_velocity;
		}


	}
	void calculate_location() {
		calculate_trace();
		//velocity += acceleration;
		pos +=velocity;
		edgedetect();
	}





};