#include "Ball.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include <stdlib.h>
#include <time.h>


Ball::Ball()
{
	TextureManager::Instance()->load("../Assets/textures/ball.png", "ball");
	srand(time(NULL));
	const auto size = TextureManager::Instance()->getTextureSize("ball");
	setWidth(40);
	setHeight(40);
	getTransform()->position = glm::vec2(rand() % 700 + 100.0f, rand() % 300 + 50.0f);
	int signx = rand() % 10;
	int signy = rand() % 15;
	getRigidBody()->velocity = glm::vec2(rand() % 200, rand() % 200);
	if (signx > 4)
		getRigidBody()->velocity *= glm::vec2(-1.0f, 1.0f);
	if (signy > 7)
		getRigidBody()->velocity *= glm::vec2(1.0f, -1.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	loss = -0.8f;
	friction = -0.05f;
	radius = getHeight() / 2.0f;
	numberOfvertices = 3;
	createPolygon(3);
	setType(TARGET);
}

Ball::~Ball()
= default;

void Ball::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance()->drawShape("ball", x, y, getWidth(), getHeight(), 0, 255, true);
	//DrawPolygon();
}

void Ball::update()
{

	if (Util::magnitude(getRigidBody()->velocity) < 10.0f)
		getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	else {
		m_move();
		m_checkBounds();
	}
	std::cout << getRigidBody()->velocity.x << "  " << getRigidBody()->velocity.y<< std::endl;
}

void Ball::clean()
{
}

void Ball::checkCollision(DisplayObject* tmpBrick)
{
	int x = getTransform()->position.x;
	int y = getTransform()->position.y;
	if (CollisionManager::circleAABBCheck(this, tmpBrick) || checkPolygonCollision(tmpBrick))
	{
		getRigidBody()->velocity = ((getRigidBody()->mass - tmpBrick->getRigidBody()->mass) * getRigidBody()->velocity /
			(getRigidBody()->mass + tmpBrick->getRigidBody()->mass)) + (
				2 * tmpBrick->getRigidBody()->mass * tmpBrick->getRigidBody()->velocity / (getRigidBody()->mass + tmpBrick->getRigidBody()->mass));
		
		tmpBrick->getRigidBody()->velocity = ((getRigidBody()->mass - tmpBrick->getRigidBody()->mass) * tmpBrick->getRigidBody()->velocity /
			(getRigidBody()->mass + tmpBrick->getRigidBody()->mass)) + (
				2 * getRigidBody()->mass * getRigidBody()->velocity / (getRigidBody()->mass + tmpBrick->getRigidBody()->mass));
	}
}

void Ball::createPolygon(int n)
{
	points.clear();
		numberOfvertices = n;
		float angle = 360.0f / n;
		for (int i = 0; i < n; i++)
		{
			points.push_back(glm::vec2(getTransform()->position.x+ radius * cos(Util::Deg2Rad * (angle * i)),
				(getTransform()->position.y + radius * sin(Util::Deg2Rad * (angle * i)))));
		}

	
}

bool Ball::checkPolygonCollision(GameObject* tmpbrick)
{
	int i;
	for (i = 0; i<points.size()-1; i++)
	{
		CollisionManager::lineRectCheck(points[i], points[i + 1],tmpbrick->getTransform()->position, tmpbrick->getWidth(), tmpbrick->getHeight());
	}
	CollisionManager::lineRectCheck(points[i], points[0], tmpbrick->getTransform()->position, tmpbrick->getWidth(), tmpbrick->getHeight());
	return false;
}

void Ball::DrawPolygon()
{
	int i;
	for (i = 0; i < points.size() - 1; i++)
	{
		Util::DrawLine(points[i], points[i + 1], glm::vec4(230.0f / 255.0f, 92.0f / 255.0f, 0.0f/255.0f,255.0f/255.0f));
	}
	Util::DrawLine(points[i], points[0], glm::vec4(230.0f / 255.0f, 92.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f));
}

void Ball::movePolygon(float deltaTime)
{
	for (int i = 0; i < points.size(); i++)
	{
		points[i]  += getRigidBody()->velocity * deltaTime;
	}
}

void Ball::m_move()
{
	float deltaTime = 1.0 / 60.0f; 
	// getRigidBody()->velocity += getRigidBody()->acceleration * deltaTime;
	getRigidBody()->velocity *= 0.99901;
	//movePolygon(deltaTime);
	getTransform()->position += getRigidBody()->velocity * deltaTime;
}

void Ball::m_checkBounds()
{
	int width = 800;
	int height = 600;
	int x = getTransform()->position.x;
	int y = getTransform()->position.y;
	if (x-radius/2 < 0)
	{
		getTransform()->position.x = 0.0 + radius / 2;
		getRigidBody()->velocity *=glm::vec2( loss,-loss);
	}
	if (y-radius / 2 < 0)
	{
		getTransform()->position.y = 0.0+ radius / 2;
		getRigidBody()->velocity*=glm::vec2(-loss, loss);
	}
	if (x +radius / 2 > 800)
	{
		getTransform()->position.x = 800- radius / 2;
		getRigidBody()->velocity *= glm::vec2(loss, -loss);
	}
	if (y + radius / 2 > 600)
	{
		getTransform()->position.y = 600- radius / 2;
		getRigidBody()->velocity *= glm::vec2(-loss, loss);
	}
}

void Ball::m_reset()
{
}
