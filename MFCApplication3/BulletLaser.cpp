#include "stdafx.h"
#include "BulletLaser.h"
BulletLaser::BulletLaser() {};
void BulletLaser::setgunman(PlaneBase *a) {
	gunman = a;
	integration.y = 0;
	pos.x = gunman->pos.x + offset.x;
	pos.y = gunman->pos.y + offset.y;
};
void BulletLaser::calculate_location() {
	pos.x = gunman->pos.x + offset.x;
	integration.y += velocity.y;
	pos.y = integration.y + gunman->pos.y + offset.y;
};
void BulletLaser::loadAnimation(Animation *a) {
	mAnimation = a;
	objectsize.x = mAnimation->slice_picture[property->pictureid][0].right;
	objectsize.y = mAnimation->slice_picture[property->pictureid][0].bottom;
	//pos = pos + *property->offset;
};
void BulletLaser::setproperty(bullet_property *a) {
	property = a;
	velocity.y = property->speed;
	mattack = property->attack;
	offset = *property->offset;
}