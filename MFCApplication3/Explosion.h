#pragma once
#include "FlyingObject.h"
class Explosion : public FlyingObject{
public:
	int index=0;
	int count = 0;
	int type;
	Explosion() :type(0) {};
	void Draw(CDC* cdc) {
		if (index > mAnimation->slice_num[type]) {
			finished = 1;
			//index = 0;
			return;
		}
		mAnimation->drawimage(cdc, pos, type,index);
		
		index++;
	}

	void Onedgeleft() {

	};
	void Onedgetop() {


	};
	void Onedgeright() {


	};
	void Onedgebottom() {

	};
	
};