#pragma once
#include "Bullet.h"


class BulletPool
{
public:
	BulletPool(int);
	~BulletPool();
	Bullet* BulletSpawn(float vel);
	void BulletDespawn(Bullet*,float,float);
	std::vector<Bullet*> active;
	int getSize() { return size; }
private:
	Bullet* m_pBullets;
	int size;
	int index = 0;


	std::vector<Bullet*> inactive;


};

