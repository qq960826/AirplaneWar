#include "stdafx.h"
#include "Explosion.h"
Explosion::Explosion() :type(0) {};
void Explosion::Draw(CDC* cdc) {
	if (index > mAnimation->slice_num[type]) {
		finished = 1;
		//index = 0;
		return;
	}
	mAnimation->drawimage(cdc, pos, type, index);

	index++;
}

void Explosion::Onedgeleft() {

};
void Explosion::Onedgetop() {


};
void Explosion::Onedgeright() {


};
void Explosion::Onedgebottom() {

};