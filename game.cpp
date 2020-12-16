#include "game.h"

#include <Windows.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "resource_manager.h"
#include "collider_manager.h"
#include "player.h"

Game::Game()
{
	level = nullptr;
	scrWidth = 0;
	scrHeight = 0;
	soundEngine = nullptr;
}

Game::~Game()
{
	ClearLevel();
}

void Game::Init(unsigned int scr_width, unsigned int scr_height)
{
	soundEngine = irrklang::createIrrKlangDevice();
	scrWidth = scr_width;
	scrHeight = scr_height;
	CreateLevel("dungeon1");
	soundEngine->play2D("./Resource/Sound/5_Dungeon_2_Master.ogg", true);
}

void Game::Update(SpriteRenderer& renderer, float deltatime)
{
	if (level->IsCleared) {
		soundEngine->stopAllSounds();
		if (level->name == "title") {
			CreateLevel("dungeon1");
			soundEngine->play2D("./Resource/Sound/5_Dungeon_2_Master.ogg", true);
		}
		else if (level->name == "dungeon1") {
			CreateLevel("dungeon2");
			soundEngine->play2D("./Resource/Sound/8_Battle_2_Master.ogg", true);
		}
		else if (level->name == "dungeon2") {
			CreateLevel("dungeon3");
			soundEngine->play2D("./Resource/Sound/10_Holy_Master.ogg", true);
		}
		else if (level->name == "dungeon3") {
			CreateLevel("bossfight");
			soundEngine->play2D("./Resource/Sound/9_Boss_1_Master.ogg", true);
		}

		level->IsCleared = false;
	}

	level->Update(renderer, deltatime);
}

void Game::FixedUpdate(float deltatime)
{
	level->FixedUpdate(deltatime);
}

void Game::ClearSingletonObjects()
{
	ResourceManager::Clear();
	ColliderManager::Delete();
}

void Game::CreateLevel(std::string file)
{
	ClearLevel();
	level = new Level;
	level->Create(file);
	level->Init();
	level->scrWidth = scrWidth;
	level->scrHeight = scrHeight;
}

void Game::ClearLevel()
{
	if (level != nullptr)
		delete level;
	level = nullptr;
}
