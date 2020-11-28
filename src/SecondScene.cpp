#include "SecondScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

#define PPM 50

SecondScene::SecondScene():activateScene(0), vertices(3), circleChecked(0), ballMass(8.0f),brickMass(12.0f)
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
	onScreenLabels[1]->setText("Ball's velocity: " + std::to_string(Util::magnitude(m_pBall->getRigidBody()->velocity)/ PPM));
	onScreenLabels[2]->setText("Brick's velocity: " + std::to_string(Util::magnitude(m_pBrick->getRigidBody()->velocity)/PPM));

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
	else
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
	SoundManager::Instance().playMusic("scene2", -1);
	// Set GUI Title
	m_guiTitle = "Play Scene";

	// Plane Sprite
	/*m_pBulletSprite = new Bullet();
	addChild(m_pBulletSprite);*/

	const SDL_Color black = { 0, 0, 0, 255 };
	onScreenLabels[0] = new Label("Press P to pause the scene and change ImGui", "Consolas", 12, black, glm::vec2(600.0f, 80.0f));
	onScreenLabels[0]->setParent(this);
	addChild(onScreenLabels[0]);

	onScreenLabels[1] = new Label("Ball's velocity: ", "Consolas", 12, black, glm::vec2(645.0f, 95.0f));
	onScreenLabels[1]->setParent(this);
	addChild(onScreenLabels[1]);

	onScreenLabels[2] = new Label("Brick's velocity: ", "Consolas", 12, black, glm::vec2(650.0f, 105.0f));
	onScreenLabels[2]->setParent(this);
	addChild(onScreenLabels[2]);

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
	ImGui::Separator();
	if (ImGui::SliderFloat("Ball mass", &ballMass, 2.0f, 20.0f))
	{
		if (!activateScene)
		{
			m_pBall->getRigidBody()->mass = ballMass;
		}
	}
	if (ImGui::SliderFloat("Brick mass", &brickMass, 2.0f, 20.0f))
	{
		if (!activateScene)
		{
			m_pBrick->getRigidBody()->mass = brickMass;
		}
	}

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
