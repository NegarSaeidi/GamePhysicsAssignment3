#pragma once
#ifndef __SECOND_SCENE__
#define __SECOND_SCENE__

#include "Scene.h"
#include "Bullet.h"
#include "Brick.h"
#include "Button.h"
#include "Label.h"
#include "Ball.h"

class SecondScene : public Scene
{
public:
	SecondScene();
	~SecondScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;

	glm::vec2 m_mousePosition;
	glm::vec2 initialPos, lastPos;
	Bullet* m_pBulletSprite;
	Ball* m_pBall;
	Brick* m_pBrick;
	bool m_playerFacingRight;
	bool movement = false;
	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;
	bool activateScene;
};

#endif /* defined (__SECOND_SCENE__) */
