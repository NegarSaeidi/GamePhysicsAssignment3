#include "BulletPool.h"
#include <iostream>

BulletPool::BulletPool(int size)
{
	this->size = size;
	for (int i = 0; i < size; i++)
	{
		inactive.push_back(new Bullet());
	}
}

BulletPool::~BulletPool()
{
}

Bullet* BulletPool::BulletSpawn(float vel)
{
	Bullet* newBullet = nullptr;
	if (inactive.size()>0)
	{
		newBullet = &m_pBullets[index];
		newBullet = inactive.back();
		newBullet->active = true;
		newBullet->setVelocity(vel);
		inactive.pop_back();
		active.push_back(newBullet);
		std::cout << "spawn\n";

	}
	return newBullet;
}

void BulletPool::BulletDespawn(Bullet* bullet,float velY,float accY)
{
	std::cout << "despawn\n";
	bullet->reset(velY,accY);
	inactive.push_back(bullet);
	for (std::vector<Bullet*>::iterator myiter = active.begin(); myiter != active.end(); myiter++)
	{
		if (*myiter == bullet)
		{
			active.erase(myiter);
			return;
		}
	}

}
