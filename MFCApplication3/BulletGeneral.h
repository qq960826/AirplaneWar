#pragma once
#include "stdafx.h"
#include "FlyingObject.h"
#include "PlaneBase.h"
class BulletGeneral:public FlyingObject {
protected:
	
public:
	int speed;
	float roataion;
	bullet_property *property;
	BulletGeneral();
	BulletGeneral(CPoint mpos, CPoint mvelocity, bullet_property *mproperty);
	BulletGeneral(CPoint mpos, bullet_property *mproperty);
	void setproperty(bullet_property *a);
	void loadAnimation(Animation *a);
	void Draw(CDC *pDoc);
	void rotate(float a);
	void Onedgeleft();
	void Onedgetop();
	void Onedgeright();
	void Onedgebottom();
	void setpictureid(int a);
};