#pragma once
#include "stdafx.h"
#include "afx.h"
#include "atltypes.h"
#include "Animation.h"
#include "MFCApplication3Doc.h"
#include "exprtk.hpp"

#include <string>
#define pi 3.1415926
struct move_equation_single {
	std::string equation;
	float base;
	float increment;
	float target;

};
struct move_equation {
	move_equation_single x;
	move_equation_single y;
};
struct move_equation_set {

	int id;
	int num_equation;
	int loop;
	CPoint offset;
	move_equation **move_equation;

};
struct bullet_property {
	int id;
	int pictureid;
	int attack;
	CPoint *offset;
	float rotation;
	int speed;
	float scale;
};
struct bullet_set {
	int id;
	int num_set;
	int *num_each;
	int *exp_each;
	bullet_property ***bullet;
};
struct plane_property {
	int id;
	int hp;
	int attack;
	int pictureid;
	int exp;
	int equation_num;
	int *equation_id;
	bullet_set *mbullet_set;
};
class FlyingObject {
private:
	int touchthreshold;

public:
	int mattack=0;//ײ��������
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
	virtual void calculate_location();
	void setAnimation(Animation *a);
	FlyingObject() :pos(0, 0), velocity(0, 0), acceleration(0, 0) {};
	FlyingObject(CPoint a, CPoint b, Animation*c) :pos(a), velocity(b), mAnimation(c){};
	FlyingObject(CPoint a, CPoint b) :pos(a), velocity(b) {};
	FlyingObject(CPoint a) :pos(a) {};
	void draw(CDC *);
	void setpos(CPoint a);
	void setvelocity(CPoint a);
	void setDoc(CMFCApplication3Doc* a) ;
	void setacceleration(CPoint a) ;
	boolean isCollsionWithPoint( CRect *b);
	boolean isCollsionWithRect(CRect b);
	void setrotation(int angle);
	void attack(FlyingObject *a);
};
