#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Bullet.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "BulletPool.h"
#include "CollisionManager.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	void collision();

private:
	 float BulletsVelocity;
	 float Bulletsacceleration;
	 float playerVel=2.5;
	bool activateScene;
	Bullet* bullet;
	// IMGUI Function
	void GUI_Function() ;
	std::string m_guiTitle;
	void spawnBullet();
	glm::vec2 m_mousePosition;
	BulletPool* m_pPool;
	const float bulletSpawnTimeDuration=300.0f;
	float bulletSpawnTimerStart;
	Player* m_pPlayer;
	bool m_playerFacingRight;
	int poolSize;
	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;
	Label* onScreenLabels[2];
};

#endif /* defined (__PLAY_SCENE__) */