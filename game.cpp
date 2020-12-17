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
	overInterval = 0.0f;
	overMax = 0.0f;
	isOver = false;
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
	overMax = 5.0f;
	CreateLevel("dungeon1");
	soundEngine->play2D("./Resource/Sound/5_Dungeon_2_Master.ogg", true);
}

void Game::Update(SpriteRenderer& renderer, float deltatime)
{
	BYTE key[256];
	bool err = 0;
	err = ::GetKeyboardState(key);

	if (key[0x31] & 0x80) {
		soundEngine->stopAllSounds();
		CreateLevel("dungeon1");
		soundEngine->play2D("./Resource/Sound/5_Dungeon_2_Master.ogg", true);
	}
	else if (key[0x32] & 0x80) {
		soundEngine->stopAllSounds();
		CreateLevel("dungeon2");
		soundEngine->play2D("./Resource/Sound/8_Battle_2_Master.ogg", true);
	}
	else if (key[0x33] & 0x80) {
		soundEngine->stopAllSounds();
		CreateLevel("dungeon3");
		soundEngine->play2D("./Resource/Sound/10_Holy_Master.ogg", true);
	}
	else if (key[0x34] & 0x80) {
		soundEngine->stopAllSounds();
		CreateLevel("bossfight");
		soundEngine->play2D("./Resource/Sound/9_Boss_1_Master.ogg", true);
	}

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
		else if (level->name == "bossfight") {
			CreateLevel("gameclear");
			soundEngine->play2D("./Resource/Sound/Stinger_Victory_2_Master.ogg", true);
		}
		level->IsCleared = false;
	}

	if (level->name == "gameover" || level->name == "gameclear")
	{
		overInterval += deltatime;
		if (overInterval >= overMax)
			isOver = true;
	}

	level->Update(renderer, deltatime);

	if (level->isOver) {
		soundEngine->stopAllSounds();
		CreateLevel("gameover");
		soundEngine->play2D("./Resource/Sound/Stinger_Transition_1_Master.ogg", true);
	}
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
