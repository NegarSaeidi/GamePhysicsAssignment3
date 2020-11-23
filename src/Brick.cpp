#include "Brick.h"
#include "TextureManager.h"


Brick::Brick()
{
	TextureManager::Instance()->load("../Assets/textures/brick.png", "circle");

	const auto size = TextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(280.0f, 540.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(TARGET);
}

Brick::~Brick()
= default;

void Brick::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance()->draw("circle", x, y, 0, 255, true);
}

void Brick::update()
{
	m_move();
	m_checkBounds();
}

void Brick::clean()
{
}

void Brick::m_move()
{
	getTransform()->position = getTransform()->position + getRigidBody()->velocity * 5.0f;
}

void Brick::m_checkBounds()
{
}

void Brick::m_reset()
{
}
