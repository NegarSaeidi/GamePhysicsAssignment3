#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	TextureManager::Instance()->load("../Assets/textures/background.png", "background");
	SoundManager::Instance().playMusic("menu", -1);

	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	TextureManager::Instance()->draw("background", 0, 0, 0, 255, false, SDL_FLIP_NONE);
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{
	
	const SDL_Color black = { 0, 0, 0, 255 };
	m_pNameLabel[0] = new Label("Negar Saeidi", "Consolas", 12, black, glm::vec2(50.0f, 10.0f));
	m_pNameLabel[0]->setParent(this);
	addChild(m_pNameLabel[0]);

	m_pNameLabel[1] = new Label("Negin Saeidi", "Consolas", 12, black, glm::vec2(50.0f, 30.0f));
	m_pNameLabel[1]->setParent(this);
	addChild(m_pNameLabel[1]);

	m_pNameLabel[2] = new Label("Mehrara Sarabi", "Consolas", 12, black, glm::vec2(55.0f, 50.0f));
	m_pNameLabel[2]->setParent(this);
	addChild(m_pNameLabel[2]);

	m_pIDLabel[0] = new Label("101261396", "Consolas", 12, black, glm::vec2(150.0f, 10.0f));
	m_pIDLabel[0]->setParent(this);
	addChild(m_pIDLabel[0]);

	m_pIDLabel[1] = new Label("101261395", "Consolas", 12, black, glm::vec2(150.0f, 30.0f));
	m_pIDLabel[1]->setParent(this);
	addChild(m_pIDLabel[1]);

	m_pIDLabel[2] = new Label("101247463", "Consolas", 12, black, glm::vec2(150.0f, 50.0f));
	m_pIDLabel[2]->setParent(this);
	addChild(m_pIDLabel[2]);


	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->getTransform()->position = glm::vec2(100.0f, 550.0f); 

	m_pStartButton->addEventListener(CLICK, [&]()-> void
	{
		m_pStartButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});
	
	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pStartButton->setAlpha(128);
	});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pStartButton->setAlpha(255);
	});
	addChild(m_pStartButton);

	//scene 2 button 
	m_pScene2Button = new Button("../Assets/textures/scene2.png", "scene2Button", SCENE2_BUTTON);
	m_pScene2Button->getTransform()->position = glm::vec2(700.0f, 550.0f);
	m_pScene2Button->addEventListener(CLICK, [&]()-> void
		{
			m_pScene2Button->setActive(false);
			TheGame::Instance()->changeSceneState(SECOND_SCENE);
		});

	m_pScene2Button->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pScene2Button->setAlpha(128);
		});

	m_pScene2Button->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pScene2Button->setAlpha(255);
		});
	addChild(m_pScene2Button);

	
}

