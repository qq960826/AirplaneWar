#include "stdafx.h"
#include "Audio.h"
Audio::Audio() {
};
void Audio::Init(CString root) {
	if (!DSlist1.Init())
		AfxMessageBox(L"Éù¿¨³õÊ¼»¯Ê§°Ü");
	CString wave_path = root + L"\\sound\\";
	DSlist1.AddNewBuffer(wave_path + "back.wav");  //buffer 0

	for (int i = 0; i < 30; i++) {
		DSlist1.AddNewBuffer(wave_path + "explosion.wav");  //buffer 0
	}
	for (int i = 0; i < 30; i++) {
		DSlist1.AddNewBuffer(wave_path + "fire.wav");  //buffer 0
	}
	DSlist1.AddNewBuffer(wave_path + "bossdie.wav");  //buffer 0
	for (int i = 0; i < 10; i++) {
		DSlist1.AddNewBuffer(wave_path + "pickup.wav");  //buffer 0
	}
	for (int i = 0; i < 10; i++) {
		DSlist1.AddNewBuffer(wave_path + "collision_plane.wav");  //buffer 0
	}
	for (int i = 0; i < 5; i++) {
		DSlist1.AddNewBuffer(wave_path + "generalplanedie.wav");  //buffer 0
	}
	for (int i = 0; i < 30; i++) {
		DSlist1.AddNewBuffer(wave_path + "laser.wav");  //buffer 0
	}

};
void Audio::PlayBackground() {
	DSlist1.PlayBuffer(0, 1);
};
void Audio::StopAll() {
	DSlist1.StopAllBuffers();
};
void Audio::PlayLaser() {
	DSlist1.PlayBuffer(music_laser_index, 0);
	music_laser_index++;
	if (music_laser_index >= 117) {
		music_laser_index = 87;
	}
};
void Audio::PlayExplosion() {
	DSlist1.PlayBuffer(music_fire_index, 0);
	music_fire_index++;
	if (music_fire_index >= 61) {
		music_fire_index = 31;

	}
};
void Audio::PlayFire() {
	DSlist1.PlayBuffer(music_explosion_index, 0);
	music_explosion_index++;
	if (music_explosion_index >= 31) {
		music_explosion_index = 1;
	}
};
void Audio::PlayPickup() {
	DSlist1.PlayBuffer(music_pickup_index, 0);
	music_pickup_index++;
	if (music_pickup_index >= 72) {
		music_pickup_index = 62;
	}
};
void Audio::PlayCollision() {
	DSlist1.PlayBuffer(music_collision_index, 0);
	music_collision_index++;
	if (music_collision_index >= 82) {
		music_collision_index = 72;
	}
};
void Audio::PlayEnemyDie() {
	DSlist1.PlayBuffer(music_enemydie_index, 0);
	music_enemydie_index++;
	if (music_enemydie_index >= 87) {
		music_enemydie_index = 82;
	}
};
void Audio::PlayWinBoss() {
	DSlist1.PlayBuffer(61, 0);
};