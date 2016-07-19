#include "stdafx.h"
#include "BulletGeneral.h";
void BulletGeneral::loadAnimation(Animation *a) {
	mAnimation = a;
	objectsize.x = mAnimation->slice_picture[property->pictureid][0].right;
	objectsize.y = mAnimation->slice_picture[property->pictureid][0].bottom;
	pos = pos + *property->offset;
};
void BulletGeneral:: Draw(CDC *pDoc) {
	//calculate_location();
	mAnimation->setrotation(roataion);
	mAnimation->setscale(property->scale);
	mAnimation->drawimage(pDoc, pos, property->pictureid, 0);


};
void BulletGeneral::rotate(float a) {
	property->rotation = a;
};
void BulletGeneral::Onedgeleft() {

	if (pos.x<-objectsize.x)finished = 1;

};
void BulletGeneral::Onedgetop() {
	if (pos.y<-objectsize.x)finished = 1;
};
void BulletGeneral::Onedgeright() {
	if (pos.x>objectsize.x + windowsize->x)finished = 1;

};
void BulletGeneral::Onedgebottom() {
	if (pos.y>objectsize.y + windowsize->y)finished = 1;

};

void BulletGeneral::setpictureid(int a) {
	property->pictureid = a;
};
BulletGeneral::BulletGeneral() {};
BulletGeneral::BulletGeneral(CPoint mpos, CPoint mvelocity, bullet_property *mproperty) :FlyingObject(mpos, mvelocity), property(mproperty) {
};
BulletGeneral::BulletGeneral(CPoint mpos, bullet_property *mproperty) :FlyingObject(mpos), property(mproperty) {
	CPoint temp_velocity;
	speed = mproperty->speed;
	roataion = mproperty->rotation;
	temp_velocity.x = -speed*sin((roataion*pi1) / 180);
	temp_velocity.y = speed*cos((roataion*pi1) / 180);

	mattack = property->attack;
	velocity = temp_velocity;


};
void BulletGeneral::setproperty(bullet_property *a) { property = a; };