#pragma once
#include "stdafx.h"
#include "FlyingObject.h"

class BulletGeneral:public FlyingObject {
protected:
	int type=0;
	float angle;
	
public:
	int attack;
	BulletGeneral(CPoint mpos,CPoint mvelocity ,int mtype,int mattack):FlyingObject(mpos,mvelocity),type(mtype), attack(mattack){
		
	};
	void loadAnimation(Animation *a);
	void Draw(CDC *pDoc);
	void rotate(float a) { angle = a; };
	void Onedgeleft() {


	};
	void Onedgetop() {
	};
	void Onedgeright() {
	
	};
	void Onedgebottom() {
		finished = 1;
	};
	CRect getlocation() {
		objectsize.x = mAnimation->slice_picture[type][0].right;
		objectsize.y = mAnimation->slice_picture[type][0].bottom;
		return CRect(pos.x, pos.y, objectsize.x, objectsize.y);
	};
	void settype(int a) {
		type = a;
		objectsize.x = mAnimation->slice_picture[type][0].right;
		objectsize.y = mAnimation->slice_picture[type][0].bottom;
	}
};