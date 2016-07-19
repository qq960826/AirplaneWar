#pragma once
#include "stdafx.h"
#include "FlyingObject.h"
class Item :public FlyingObject {
public:
	struct item_properity property;
	Item();
	void loadproperty(item_properity a);
	void loadAnimation(Animation *a);
	void Draw(CDC *pDoc);
};