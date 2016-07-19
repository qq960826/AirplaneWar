#pragma once
#include "FlyingObject.h"
class Explosion : public FlyingObject{
public:
	int index=0;
	int count = 0;
	int type;
	Explosion();
	void Draw(CDC* cdc);
	void Onedgeleft();
	void Onedgetop();
	void Onedgeright();
	void Onedgebottom();
};