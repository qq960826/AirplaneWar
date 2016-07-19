#pragma once
#include "stdafx.h"
#include "atltypes.h"

#include "DSBuffer.h"
#include "DSList.h"
class Audio {
private:
	CDSList DSlist1;
	int music_explosion_index = 1;
	int music_fire_index = 31;
	int music_pickup_index = 62;
	int music_collision_index = 72;
	int music_enemydie_index = 82;
	int music_laser_index = 87;
public:
	Audio();
	void Init(CString root);
	void PlayBackground();
	void StopAll();
	void PlayLaser();
	void PlayExplosion();
	void PlayFire();
	void PlayPickup();
	void PlayCollision();
	void PlayEnemyDie();
	void PlayWinBoss();
};