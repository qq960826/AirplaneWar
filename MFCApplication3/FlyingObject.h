#pragma once
#include "stdafx.h"
#include "afx.h"
#include "atltypes.h"
#include "Animation.h"
#include "MFCApplication3Doc.h"

class FlyingObject {
private:
	int touchthreshold;

public:
	int mattack=0;//×²»ú¹¥»÷Á¦
	int hp=0;
	CMFCApplication3Doc* pDoc;
	CPoint pos;
	CPoint velocity;
	CPoint acceleration;
	CPoint *windowsize;
	CPoint objectsize;
	Animation *mAnimation;
	int finished = 0;

public:
	void setattack(int a);
	void edgedetect();
	virtual void Onedgeleft() = 0;
	virtual void Onedgetop() = 0;
	virtual void Onedgeright() = 0;
	virtual void Onedgebottom() = 0;
	void calculate_location();
	void setAnimation(Animation *a);
	FlyingObject() :pos(0, 0), velocity(0, 0), acceleration(0, 0) {};
	FlyingObject(CPoint a, CPoint b, Animation*c) :pos(a), velocity(b), mAnimation(c){};
	FlyingObject(CPoint a, CPoint b) :pos(a), velocity(b) {};
	void draw(CDC *);
	void setpos(CPoint a);
	void setvelocity(CPoint a);
	void setobjectsize(CPoint a);
	void setDoc(CMFCApplication3Doc* a) ;
	void setacceleration(CPoint a) ;
	boolean isCollsionWithPoint( CRect *b);
	boolean isCollsionWithRect(CRect b);
	void setrotation(int angle);
	void attack(FlyingObject *a);
};
