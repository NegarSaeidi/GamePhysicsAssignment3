#include "Bullet.h"
#include "TextureManager.h"

Bullet::Bullet()
{
	TextureManager::Instance()->load("../Assets/textures/bullet.png", "bullet");
	const auto size = TextureManager::Instance()->getTextureSize("bullet");
	// set frame width
	setWidth(size.x);
	setHeight(size.y);
	//setWidth(65);

	// set frame height
	setHeight(65);

	getTransform()->position = glm::vec2(400.0f, 200.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 9.8f);
	setType(PLANE);
	reset(100.0f,9.8f);
	//m_buildAnimations();
}
Bullet::~Bullet()
= default;

void Bullet::draw()
{
	// alias for x and y
	if (active)
	{
		const auto x = getTransform()->position.x;
		const auto y = getTransform()->position.y;

		// draw the target
		if(getRigidBody()->isColliding==false)
		TextureManager::Instance()->draw("bullet", x, y, 0, 255, true);
	}
}

void Bullet::update()
{
	if (active)
	move();
}

void Bullet::clean()
{
}

void Bullet::move()
{
	float deltaTime = 1.0f / 60.0f;
	
	getRigidBody()->velocity = getRigidBody()->velocity + (getRigidBody()->acceleration * deltaTime);
	getTransform()->position = getTransform()->position+getRigidBody()->velocity*deltaTime;
	
}
void Bullet::setVelocity(float velY)
{
	getRigidBody()->velocity = glm::vec2(0, velY);

}
void Bullet::reset(float velY,float accY)
{
	getRigidBody()->velocity = glm::vec2(0.0f, velY);
	getRigidBody()->acceleration = glm::vec2(0.0f, accY);
	getRigidBody()->isColliding = false;
	active = false;
}

void Bullet::m_buildAnimations()
{
	Animation planeAnimation = Animation();

	planeAnimation.name = "plane";
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane1"));
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane2"));
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane3"));

	setAnimation(planeAnimation);
}