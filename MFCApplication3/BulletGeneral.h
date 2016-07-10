#pragma once
#include "stdafx.h"
#include "FlyingObject.h"
#include "PlaneBase.h"
class BulletGeneral:public FlyingObject {
protected:
	
public:
	//int attack;
	bullet_property *property;
	BulletGeneral(CPoint mpos,CPoint mvelocity ,bullet_property *mproperty):FlyingObject(mpos,mvelocity), property(mproperty){


	};
	BulletGeneral(CPoint mpos, bullet_property *mproperty) :FlyingObject(mpos), property(mproperty) {
		CPoint temp_velocity;
		temp_velocity.x = -mproperty->speed*sin((mproperty->rotation*pi) / 180);
		temp_velocity.y = mproperty->speed*cos((mproperty->rotation*pi) / 180);
		velocity = temp_velocity;


	};
	void loadAnimation(Animation *a);
	void Draw(CDC *pDoc);
	void rotate(float a) { 
		property->rotation = a;
	};
	void Onedgeleft() {


	};
	void Onedgetop() {
	};
	void Onedgeright() {
	
	};
	void Onedgebottom() {
		if(pos.y>objectsize.y+windowsize->y)finished = 1;
		
	};
	CRect getlocation() {

		return CRect(pos.x, pos.y, objectsize.x, objectsize.y);
	};
	void setpictureid(int a) {
		property->pictureid = a;
	}
};