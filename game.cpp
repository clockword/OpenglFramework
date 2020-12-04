#include "game.h"

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

void Game::Init(const unsigned int scr_width, const unsigned int scr_height)
{
    //ResourceManager::LoadShader("vs_sprite.glsl", "fs_sprite.glsl", nullptr, "sprite");
    //glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(scr_width), static_cast<float>(scr_height), 0.0f, -1.0f, 1.0f);
    //ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
    //ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    //Shader temp = ResourceManager::GetShader("sprite");
    //SpriteRenderer renderer(temp);

    //CollObject obj({ 1000.0f,100.0f }, { 1.0f,1.0f }, ResourceManager::LoadTexture(((std::string)"./Resource/Image/dog.png").c_str(), true, "dog"));
    //obj.Create(ResourceManager::LoadAnims(((std::string)"./Resource/VertexData/dog.txt").c_str(), *obj.Sprite, "dog"),
    //    ColliderManager::LoadCollider(((std::string)"./Resource/ColliderData/dog.txt").c_str(), "dog"));

    //Player player({ 500.0f,100.0f }, { 1.0f,1.0f }, ResourceManager::LoadTexture(((std::string)"./Resource/Image/dog.png").c_str(), true, "dog"));
    //player.Create(ResourceManager::LoadAnims(((std::string)"./Resource/VertexData/dog.txt").c_str(), *player.Sprite, "dog"),
    //    ColliderManager::LoadCollider(((std::string)"./Resource/ColliderData/dog.txt").c_str(), "dog"));

    //obj.xFlip = true;
    //obj.yFlip = true;
}

void Game::Update(SpriteRenderer& renderer, float deltatime)
{
    //player.Update(renderer, deltaTime);
    //obj.Update(renderer, deltaTime);
	level->Update(renderer, deltatime);
}

void Game::FixedUpdate(float deltatime)
{
    //ColliderManager::FixedUpdate(deltatime);
	level->FixedUpdate(deltatime);
}

void Game::ClearSingletonObjects()
{
	ResourceManager::Clear();
	ColliderManager::Delete();
}

void Game::CreateLevel(std::string file)
{
	if (level == nullptr)
		return;
	level = new Level;
	level->Create(file);
}

void Game::ClearLevel()
{
    //ResourceManager::Clear();
    //ColliderManager::Delete();
	if (level != nullptr)
		delete level;
}
