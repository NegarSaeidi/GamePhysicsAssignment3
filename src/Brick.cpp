#include "Brick.h"
#include "Util.h"
#include "TextureManager.h"


Brick::Brick()
{
	TextureManager::Instance()->load("../Assets/textures/brick.png", "circle");

	const auto size = TextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(280.0f, 540.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;
	getRigidBody()->mass = 12.0f;
	m_pDirection = glm::vec2(0.0f, 0.0f);
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

void Brick::setDir(glm::vec2 dir)
{
	m_pDirection = dir;
	
}

void Brick::stop()
{
	m_pDirection = glm::vec2(0, 0);
}

void Brick::m_move()
{
	
	//getTransform()->position = getTransform()->position + getRigidBody()->velocity * 5.0f;
	const float deltaTIme = 1.0f / 60.0f;
	float dirMagnitude = Util::magnitude(m_pDirection);
	if (dirMagnitude > 0)
	{
		std::cout << "moving\n";
		getRigidBody()->acceleration = Util::normalize(m_pDirection) * ACCELERATION;
	}
	else if (Util::magnitude(getRigidBody()->velocity) > 0)
	{
		std::cout << "slowing\n";
		getRigidBody()->acceleration = Util::normalize(getRigidBody()->velocity) * -ACCELERATION;
		if (Util::magnitude(getRigidBody()->velocity) < ACCELERATION)
		{
			std::cout << "ending\n";
			getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
			getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);

			//getRigidBody()->acceleration = glm::vec2(-getRigidBody()->velocity.x, -getRigidBody()->velocity.y);
		}
	}

	getRigidBody()->velocity += getRigidBody()->acceleration;
	glm::vec2 pos = getTransform()->position;
	pos.x += getRigidBody()->velocity.x * deltaTIme;
	pos.y += getRigidBody()->velocity.y * deltaTIme;
	getTransform()->position = pos;
}

void Brick::m_checkBounds()
{
}

void Brick::m_reset()
{
}
