#pragma once
#ifndef __BALL__
#define __BALL__

#include "DisplayObject.h"
#include "Util.h"

class Ball final : public DisplayObject {
public:
	Ball();
	~Ball();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:
	void m_move();
	void m_checkBounds();
	void m_reset();

	float loss;
	float radius;
};


#endif /* defined (__TARGET__) */