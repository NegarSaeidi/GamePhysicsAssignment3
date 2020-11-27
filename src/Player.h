#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "PlayerAnimationState.h"
#include "Sprite.h"

class Player final : public Sprite
{
public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	void moveLeft();
	void moveRight();
	// setters
	void setAnimationState(PlayerAnimationState new_state);
	void stop();
private:
	float ACCELERATION= 1;
	float SPEED =1.0f;
	void m_buildAnimations();
	glm::vec2 m_pDirection;
	PlayerAnimationState m_currentAnimationState;
	void m_checkBounds();
	float radius;
};

#endif /* defined (__PLAYER__) */