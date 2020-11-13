#pragma once
#include "Bullet.h"


class BulletPool
{
public:
	BulletPool(int);
	~BulletPool();
	Bullet* BulletSpawn();
	void BulletDespawn(Bullet*);
private:
	Bullet* m_pBullets;
	int size;
	int index = 0;

	std::vector<Bullet*> active;
	std::vector<Bullet*> inactive;


};

