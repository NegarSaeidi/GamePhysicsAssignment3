#pragma once
#ifndef __BRICK__
#define __BRICK__

#include "DisplayObject.h"

class Brick final : public DisplayObject {
public:
	Brick();
	~Brick();
	glm::vec2 m_pDirection;
	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	void setDir(glm::vec2);

	void stop();
private:
	float ACCELERATION = 5;
	float SPEED = 6.0f;
	
	void m_move();
	void m_checkBounds();
	void m_reset();
};


#endif /* defined (__TARGET__) */