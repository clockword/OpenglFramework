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
}

Game::~Game()
{
	ClearLevel();
}

void Game::Init()
{
	CreateLevel("./Resource/Level/dungeon3.txt");
	level->Init();
}

void Game::Update(SpriteRenderer& renderer, float deltatime)
{
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
}

void Game::ClearLevel()
{
	if (level != nullptr)
		delete level;
	level = nullptr;
}
