#pragma once
#ifndef __BULLET__
#define __BULLET__

#include "Sprite.h"

class Bullet final : public Sprite
{
public:
	Bullet();
	~Bullet();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	void move();
	void reset(float velY, float accY);
	bool active = false;
private:
	void m_buildAnimations();
	
};

#endif /* defined (__PLANE__) */
