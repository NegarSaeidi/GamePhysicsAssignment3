#pragma once
#ifndef __BALL__
#define __BALL__

#include "DisplayObject.h"
#include "Util.h"
#include "BallShape.h"
#include <vector>
class Ball final : public DisplayObject {
public:
	Ball();
	~Ball();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	void checkCollision(DisplayObject* tmpBrick);
	void createPolygon(int n);
	bool checkPolygonCollision(GameObject* tmpbrick);
	void DrawPolygon();
	void movePolygon(float deltaTime);
	int getNumOfVertices();
	void setNumOfVertices(int num);
	void setBallShape(BallShape bs);

private:
	void m_move();
	void m_checkBounds();
	void m_reset();
	
	BallShape ballshape;
	float loss;
	float friction;
	float radius;
	int numberOfvertices;
	std::vector<glm::vec2> points;
};


#endif /* defined (__TARGET__) */