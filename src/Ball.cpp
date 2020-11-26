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
	radius = getHeight() / 2.0f;
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
}

void Ball::update()
{
	if (Util::magnitude(getRigidBody()->velocity) < 20.0f)
		getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	else {
		m_move();
		m_checkBounds();
	}
}

void Ball::clean()
{
}

void Ball::checkCollision(DisplayObject* tmpBrick)
{
	int x = getTransform()->position.x;
	int y = getTransform()->position.y;
	if (CollisionManager::circleAABBCheck(this, tmpBrick))
	{
		getRigidBody()->velocity = ((getRigidBody()->mass - tmpBrick->getRigidBody()->mass) * getRigidBody()->velocity /
			(getRigidBody()->mass + tmpBrick->getRigidBody()->mass)) + (
				2 * tmpBrick->getRigidBody()->mass * tmpBrick->getRigidBody()->velocity / (getRigidBody()->mass + tmpBrick->getRigidBody()->mass));
		
		tmpBrick->getRigidBody()->velocity = ((getRigidBody()->mass - tmpBrick->getRigidBody()->mass) * tmpBrick->getRigidBody()->velocity /
			(getRigidBody()->mass + tmpBrick->getRigidBody()->mass)) + (
				2 * getRigidBody()->mass * getRigidBody()->velocity / (getRigidBody()->mass + tmpBrick->getRigidBody()->mass));
	}
}

void Ball::m_move()
{
	float deltaTime = 1.0 / 60.0f; 
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
