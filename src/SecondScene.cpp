#include "SecondScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

SecondScene::SecondScene():activateScene(0), vertices(3), circleChecked(0), ballMass(),brickMass()
{
	TextureManager::Instance()->load("../Assets/textures/scene2bg.png", "background");
	SecondScene::start();
}

SecondScene::~SecondScene()
= default;

void SecondScene::draw()
{
	TextureManager::Instance()->draw("background", 0, 0, 0, 255, false, SDL_FLIP_NONE);
	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void SecondScene::update()
{
	if (activateScene)
	{
		m_pBall->checkCollision(m_pBrick);
		lastPos = EventManager::Instance().getMousePosition();
		glm::vec2 direction = (lastPos - m_pBrick->getTransform()->position);
		m_pBrick->getRigidBody()->velocity = direction * 1.25f;
		if (abs(Util::magnitude(m_pBrick->getTransform()->position - EventManager::Instance().getMousePosition()) < 10))
		{
			m_pBrick->setDir(glm::vec2(0.0f, 0.0f));
			m_pBrick->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		}
		updateDisplayList();
	}
	m_pBackButton->update();
}

void SecondScene::clean()
{
	removeAllChildren();
}

void SecondScene::handleEvents()
{

	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_P))
	{
		activateScene = false;
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}



void SecondScene::start()
{
	//SoundManager::Instance().playMusic("scene2", -1);
	// Set GUI Title
	m_guiTitle = "Play Scene";

	// Plane Sprite
	/*m_pBulletSprite = new Bullet();
	addChild(m_pBulletSprite);*/

	// Brick Sprite
	m_pBrick = new Brick();
	addChild(m_pBrick);
	m_playerFacingRight = true;


	//ball Sprite
	m_pBall = new Ball();
	addChild(m_pBall);

	// Back Button
	m_pBackButton = new Button("../Assets/textures/back.png", "back", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(700.0f, 50.0f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
	{
		m_pBackButton->setActive(false);
		TheGame::Instance()->changeSceneState(START_SCENE);
	});

	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pBackButton->setAlpha(128);
	});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pBackButton->setAlpha(255);
	});
	addChild(m_pBackButton);

	//// Next Button
	//m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
	//m_pNextButton->getTransform()->position = glm::vec2(500.0f, 400.0f);
	//m_pNextButton->addEventListener(CLICK, [&]()-> void
	//	{
	//		m_pNextButton->setActive(false);
	//		TheGame::Instance()->changeSceneState(END_SCENE);
	//	});

	//m_pNextButton->addEventListener(MOUSE_OVER, [&]()->void
	//	{
	//		m_pNextButton->setAlpha(128);
	//	});

	//m_pNextButton->addEventListener(MOUSE_OUT, [&]()->void
	//	{
	//		m_pNextButton->setAlpha(255);
	//	});

	//addChild(m_pNextButton);

	///* Instructions Label */
	//m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas");
	//m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 500.0f);

	//addChild(m_pInstructionsLabel);
}

void SecondScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Change the variables", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if (ImGui::Button("Activate"))
	{
		activateScene = true;
	}

	ImGui::Separator();

	if (ImGui::SliderInt("Polygon number of vertices ", &vertices, 3, 8))
	{
		if (!activateScene && !circleChecked)
		{
			m_pBall->setNumOfVertices(vertices);
		}
	}
	if (ImGui::Checkbox("Circle", &circleChecked));
	{
		if (!activateScene && circleChecked)
		{
			m_pBall->setBallShape(CIRCLE);
		}
		if (!circleChecked && !activateScene)
		{
			m_pBall->setBallShape(POLYGON);
		}
	}


	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
