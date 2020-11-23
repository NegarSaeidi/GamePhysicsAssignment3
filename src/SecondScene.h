#pragma once
#ifndef __SECOND_SCENE__
#define __SECOND_SCENE__

#include "Scene.h"
#include "Bullet.h"
#include "Brick.h"
#include "Button.h"
#include "Label.h"

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
	void GUI_Function() const;
	std::string m_guiTitle;

	glm::vec2 m_mousePosition;

	Bullet* m_pBulletSprite;
	Brick* m_pBrick;
	bool m_playerFacingRight;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;
};

#endif /* defined (__SECOND_SCENE__) */
