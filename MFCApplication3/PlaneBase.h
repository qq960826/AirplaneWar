#pragma once
#include "stdafx.h"
#include "FlyingObject.h"
#include "BulletGeneral.h"
struct bullet_property {
	int id;
	int pictureid;
	int attack;
	CPoint *offset;
	float rotation;
	int speed;
	float scale;
};
struct bullet_set {
	int id;
	int num_set;
	int *num_each;
	bullet_property ***bullet;
};
struct plane_property {
	int id;
	int hp;
	int attack;
	int pictureid;
	bullet_set *mbullet_set;
};
class PlaneBase:public FlyingObject {
protected:
	
	
	
public :
	int shape;
	plane_property mproperty;

	PlaneBase() :FlyingObject() {};
	void draw(CDC *);
	void fire(CObList *bullet);
	CRect getlocation();
	bool isCollsion(CRect a);
	void setproperty(plane_property a) {
		mproperty = a;
	}
};