#include "Player.h"
#include "TextureManager.h"
#include "Util.h"


Player::Player(): m_currentAnimationState(PLAYER_IDLE_RIGHT)
{
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas11.png", 
		"spritesheet");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("spritesheet"));
	
	// set frame width
	setWidth(53);

	// set frame height
	setHeight(58);

	getTransform()->position = glm::vec2(380.0f, 540.0f);
	getRigidBody()->velocity = glm::vec2(1.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(1.0f, 0.0f);
	getRigidBody()->isColliding = false;
	m_pDirection = glm::vec2(0.0f,0.0f);
	setType(PLAYER);
	
	m_buildAnimations();
}

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the player according to animation state
	switch(m_currentAnimationState)
	{
	case PLAYER_IDLE_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("idle"),
			x, y, 0.12f, 0, 255, true);
		break;
	case PLAYER_IDLE_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("idle"),
			x, y, 0.12f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_RUN_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("run"),
			x, y, 0.25f, 0, 255, true);
		break;
	case PLAYER_RUN_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("run"),
			x, y, 0.25f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	default:
		break;
	}
	
}

void Player::update()
{
	const float deltaTIme = 1.0f / 60.0f;
	float dirMagnitude = Util::magnitude(m_pDirection); 
	if (dirMagnitude > 0)
	{
		
		getRigidBody()->acceleration = Util::normalize(m_pDirection) * ACCELERATION;
	}
	else if (Util::magnitude(getRigidBody()->velocity) > 10)
	{
		getRigidBody()->acceleration = Util::normalize(getRigidBody()->velocity) * -ACCELERATION;
	}
	else
	{
		getRigidBody()->acceleration = glm::vec2(-getRigidBody()->velocity.x, -getRigidBody()->velocity.y);
	}

	getRigidBody()->velocity += getRigidBody()->acceleration;
	glm::vec2 pos = getTransform()->position;
	pos.x += getRigidBody()->velocity.x * deltaTIme;
	getTransform()->position = pos;
}

void Player::clean()
{
}

void Player::moveLeft()
{
	
	m_pDirection.x = -1;
}

void Player::moveRight()
{
	m_pDirection.x = 1;
}

void Player::setAnimationState(const PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void Player::stop()
{
	m_pDirection.x =0;
}

void Player::m_buildAnimations()
{
	Animation idleAnimation = Animation();

	idleAnimation.name = "idle";
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-0"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-1"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-2"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-3"));

	setAnimation(idleAnimation);

	Animation runAnimation = Animation();

	runAnimation.name = "run";
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-0"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-1"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-2"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-3"));

	setAnimation(runAnimation);
}
