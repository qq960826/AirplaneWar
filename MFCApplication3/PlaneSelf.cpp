#include "stdafx.h"
#include "PlaneSelf.h"
void PlaneSelf::Onedgeleft() {
	pos.x = 0;
	if (velocity.x < 0)velocity.x = 0;
};
void PlaneSelf::Onedgetop() {
	pos.y = 0;
	velocity.y = 0;

};
void PlaneSelf::Onedgeright() {
	pos.x = windowsize->x - objectsize.x;
	if (velocity.x> 0)velocity.x = 0;

};
void PlaneSelf::Onedgebottom() {
	pos.y = windowsize->y - objectsize.y;
	if (velocity.y < 0)velocity.y = 0;
};

