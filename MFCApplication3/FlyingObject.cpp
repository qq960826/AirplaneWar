#pragma once
#include "stdafx.h"
#include "resource.h"
#include "FlyingObject.h"

FlyingObject::FlyingObject() :pos(0, 0), velocity(0, 0), acceleration(0, 0) {};
FlyingObject::FlyingObject(CPoint a, CPoint b, Animation*c) :pos(a), velocity(b), mAnimation(c) {};
FlyingObject::FlyingObject(CPoint a, CPoint b) :pos(a), velocity(b) {};
FlyingObject::FlyingObject(CPoint a) :pos(a) {};
void FlyingObject::calculate_location() {
	
	velocity += acceleration;
	pos += velocity;
	edgedetect();
};


void  FlyingObject::setpos(CPoint a) {
	pos = a;
};
void FlyingObject::setvelocity(CPoint a) {
	velocity = a;
};

void  FlyingObject::setDoc(CMFCApplication3Doc* a) {
	pDoc = a;
	windowsize = pDoc->windowssize;
};
void FlyingObject::setacceleration(CPoint a) {
	acceleration = a;
};

boolean FlyingObject::isCollsionWithPoint(CRect *b) {
	if (pos.x >= b->left && pos.x <= b->left + b->right && pos.y >= b->top && pos.y <= b->top + b->bottom) {
		return true;
	}
	return false;
};

boolean FlyingObject::isCollsionWithRect(CRect b) {
	if (pos.x >= b.left && pos.x >= b.left + b.right) {
		return false;
	}
	else if (pos.x <= b.left && pos.x + objectsize.x <= b.left) {
		return false;
	}
	else if (pos.y >= b.top && pos.y >= b.top + b.bottom) {
		return false;
	}
	else if (pos.y <= b.top && pos.y + objectsize.y <= b.top) {
		return false;
	}
	return true;
};
void FlyingObject::setrotation(int angle) {


	mAnimation->setrotation(angle);

}

void  FlyingObject::attack(FlyingObject *a) {
	hp -= a->mattack;
	a->hp -= mattack;
}

void FlyingObject::setattack(int a) { mattack = a; }
void FlyingObject::edgedetect() {
	if (pos.x < 0) {
		Onedgeleft();

	}
	if (pos.y < 0) {
		Onedgetop();
	}
	if (pos.y + objectsize.y > windowsize->y) {
		Onedgebottom();

	}
	if (pos.x > windowsize->x - objectsize.x) {
		Onedgeright();

	}

};
void FlyingObject::setAnimation(Animation *a) {

	mAnimation = a;
};
CRect FlyingObject::getlocation() {

	return CRect(pos.x, pos.y, objectsize.x, objectsize.y);
};