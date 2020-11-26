#include "SecondScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

SecondScene::SecondScene()
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
	updateDisplayList();
}

void SecondScene::clean()
{
	removeAllChildren();
}

void SecondScene::handleEvents()
{

	EventManager::Instance().update();

	// handle player movement with GameController
	if (SDL_NumJoysticks() > 0)
	{
		if (EventManager::Instance().getGameController(0) != nullptr)
		{
			const auto deadZone = 10000;
			if (EventManager::Instance().getGameController(0)->LEFT_STICK_X > deadZone)
			{
			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_X < -deadZone)
			{
				
				m_playerFacingRight = false;
			}
			else
			{
				if (m_playerFacingRight)
				{
					
				}
				else
				{
					
				}
			}
		}
	}


	// handle player movement if no Game Controllers found
	if (SDL_NumJoysticks() < 1)
	{
		if ((EventManager::Instance().getMouseButton(0)) && !movement)
			initialPos = EventManager::Instance().getMousePosition();;
		if (EventManager::Instance().getMouseButton(0))
		{
			lastPos = EventManager::Instance().getMousePosition();
			m_pBrick->setDir(lastPos - initialPos);
			m_pBrick->getTransform()->position = EventManager::Instance().getMousePosition();
			movement = true;
		}
		
		else
		{
			m_pBrick->stop();
			movement = false;
		}


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

	// Brick Sprite
	m_pBrick = new Brick();
	addChild(m_pBrick);
	m_playerFacingRight = true;


	//ball Sprite
	m_pBall = new Ball();
	addChild(m_pBall);

	// Back Button
	//m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	//m_pBackButton->getTransform()->position = glm::vec2(300.0f, 600.0f);
	//m_pBackButton->addEventListener(CLICK, [&]()-> void
	//	{
	//		m_pBackButton->setActive(false);
	//		TheGame::Instance()->changeSceneState(START_SCENE);
	//	});

	//m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	//	{
	//		m_pBackButton->setAlpha(128);
	//	});

	//m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	//	{
	//		m_pBackButton->setAlpha(255);
	//	});
	//addChild(m_pBackButton);

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

void SecondScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if (ImGui::Button("My Button"))
	{
		std::cout << "My Button Pressed" << std::endl;
	}

	ImGui::Separator();

	static float float3[3] = { 0.0f, 1.0f, 1.5f };
	if (ImGui::SliderFloat3("My Slider", float3, 0.0f, 2.0f))
	{
		std::cout << float3[0] << std::endl;
		std::cout << float3[1] << std::endl;
		std::cout << float3[2] << std::endl;
		std::cout << "---------------------------\n";
	}

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
