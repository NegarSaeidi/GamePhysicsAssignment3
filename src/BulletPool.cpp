#include "BulletPool.h"

BulletPool::BulletPool(int size)
{
	for (int i = 0; i < size; i++)
	{
		inactive.push_back(new Bullet());
	}
}

BulletPool::~BulletPool()
{
}

Bullet* BulletPool::BulletSpawn()
{
	Bullet* newBullet = nullptr;
	if (inactive.size()>0)
	{
		newBullet = &m_pBullets[index];
		newBullet = inactive.back();
		newBullet->active = true;
		inactive.pop_back();
		active.push_back(newBullet);

	}
	return newBullet;
}

void BulletPool::BulletDespawn(Bullet* bullet,float velY,float accY)
{
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
