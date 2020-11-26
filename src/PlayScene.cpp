#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlayScene::PlayScene()
{
	TextureManager::Instance()->load("../Assets/textures/scene1.png", "background");
	BulletsVelocity = 100.0f;
	Bulletsacceleration = 9.8f;
	poolSize = 10;
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance()->draw("background", 0, 0, 0, 255, false, SDL_FLIP_NONE);
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();
	if (activateScene)
	{
	
		if (SDL_GetTicks() - bulletSpawnTimerStart >= bulletSpawnTimeDuration)
		{
			spawnBullet();
		}
		collision();
		for (std::vector<Bullet*>::iterator myiter = m_pPool->active.begin(); myiter != m_pPool->active.end(); myiter++)
		{
			Bullet* tempBullet = *myiter;
			if ((*myiter)->getTransform()->position.y >= 650)
			{
				m_pPool->BulletDespawn(tempBullet, BulletsVelocity,Bulletsacceleration);
				removeChild(tempBullet);
				break;

			}
		}
	}

}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
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
				m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
				m_playerFacingRight = true;
			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_X < -deadZone)
			{
				m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
				m_playerFacingRight = false;
			}
			else
			{
				if (m_playerFacingRight)
				{
					m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
				}
				else
				{
					m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
				}
			}
		}
	}


	// handle player movement if no Game Controllers found
	if (SDL_NumJoysticks() < 1)
	{
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
			m_pPlayer->moveLeft();
			m_playerFacingRight = false;
		}
		
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
			m_pPlayer->moveRight();
			m_playerFacingRight = true;
		}
			//m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
		
		
		else
		{
			if (m_playerFacingRight)
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
				m_pPlayer->stop();
			}
			else
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
				m_pPlayer->stop();
			}
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
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_M))
	{
		
	}
}

void PlayScene::start()
{
	// Set GUI Title
	SoundManager::Instance().playMusic("scene1", -1);
	m_guiTitle = "Play Scene";
	
	 //Bullet Sprite
	m_pPool = new BulletPool(poolSize);

	bulletSpawnTimerStart = SDL_GetTicks();
	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);
	m_playerFacingRight = true;

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

void PlayScene::collision()
{
	

	for (std::vector<Bullet*>::iterator myiter = m_pPool->active.begin(); myiter != m_pPool->active.end(); myiter++)
	{
		Bullet* tempBullet = *myiter;
		if (CollisionManager::squaredRadiusCheck((*myiter), m_pPlayer))
		{
			if (tempBullet->getRigidBody()->isColliding == false)
			{
				
				SoundManager::Instance().playSound("boom", 0);
				tempBullet->getRigidBody()->isColliding = true;
			}

		}
	}
		
		
}

void PlayScene::spawnBullet()
{
	 bullet = m_pPool->BulletSpawn();
	if (bullet)
	{
		addChild(bullet);
		bullet->getTransform()->position = glm::vec2(50 + rand() % 700, 0);
	}
	bulletSpawnTimerStart = SDL_GetTicks();
}

void PlayScene::GUI_Function() 
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Change the variables", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if(ImGui::Button("Activate"))
	{
		 activateScene = true;
	}

	ImGui::Separator();

	
	if (ImGui::SliderFloat("Bullets' velocity", &BulletsVelocity, 0.0f, 400.0f))
	{

		for (std::vector<Bullet*>::iterator myiter = m_pPool->active.begin(); myiter != m_pPool->active.end(); myiter++)
		{
			Bullet* tempBullet = *myiter;
			tempBullet->getRigidBody()->velocity.y = BulletsVelocity;

		}
	}
	//if (ImGui::SliderFloat("Player's velocity", &playerVel, 1.0f, 10.f))
	//{

	//	m_pPlayer->getRigidBody()->velocity.x = playerVel;
	//}
	if (ImGui::SliderInt("Bullet pool", &poolSize, 1.0f, 20.0f))
	{
		
		m_pPool = nullptr;
		poolSize++;
		m_pPool = new BulletPool(poolSize);
		std::cout << "Size " << m_pPool->getSize() << std::endl;
	}
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
