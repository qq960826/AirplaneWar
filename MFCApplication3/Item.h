#pragma once
#include "FlyingObject.h"
class Item :public FlyingObject {
public:
	struct item_properity property;
	//int type;//0Ϊ��hp��1Ϊ���ⵯ��2Ϊ������
	//int value;
	Item() {};

	void loadproperty(item_properity a) {
		property = a;
		//type = a->type;
		//value=a->
		
	}
	void loadAnimation(Animation *a) {
		mAnimation = a;
		objectsize.x = mAnimation->slice_picture[property.pictureid[0]][0].right;
		objectsize.y = mAnimation->slice_picture[property.pictureid[0]][0].bottom;
	};
	void Draw(CDC *pDoc) {
		//calculate_location();
		//mAnimation->setrotation(roataion);
		mAnimation->setscale(property.scale);
		mAnimation->drawimage(pDoc, pos, property.pictureid[0], 0);


	};

};