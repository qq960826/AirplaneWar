#include "stdafx.h"
#include "Item.h"
Item::Item() {};

void Item::loadproperty(item_properity a) {
	property = a;
}
void Item::loadAnimation(Animation *a) {
	mAnimation = a;
	objectsize.x = mAnimation->slice_picture[property.pictureid[0]][0].right;
	objectsize.y = mAnimation->slice_picture[property.pictureid[0]][0].bottom;
};
void Item::Draw(CDC *pDoc) {
	mAnimation->setscale(property.scale);
	mAnimation->drawimage(pDoc, pos, property.pictureid[0], 0);
};