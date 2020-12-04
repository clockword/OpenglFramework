#include "solo_sprite.h"
#include "resource_manager.h"

SoloSprite::SoloSprite()
{
	animIndex = 0;
	animInterval = 0.0f;
	animIntervalMax = 100.0f;
	Position = glm::vec2(0.0f, 0.0f);
	Size = glm::vec2(1.0f, 1.0f);
	Width = 0;
}

void SoloSprite::PushSprite()
{
	objects.push_back(ResourceManager::LoadTexture("./Resource/Backgrounds/Dungeon2/layer_10.png", false, "layer_10"));
	objects.push_back(ResourceManager::LoadTexture("./Resource/Backgrounds/Dungeon2/layer_11.png", false, "layer_11"));
	objects.push_back(ResourceManager::LoadTexture("./Resource/Backgrounds/Dungeon2/layer_12.png", false, "layer_12"));
	objects.push_back(ResourceManager::LoadTexture("./Resource/Backgrounds/Dungeon2/layer_13.png", false, "layer_13"));
	objects.push_back(ResourceManager::LoadTexture("./Resource/Backgrounds/Dungeon2/layer_14.png", false, "layer_14"));
	objects.push_back(ResourceManager::LoadTexture("./Resource/Backgrounds/Dungeon2/layer_15.png", false, "layer_15"));
	objects.push_back(ResourceManager::LoadTexture("./Resource/Backgrounds/Dungeon2/layer_16.png", false, "layer_16"));
}

void SoloSprite::Update(SpriteRenderer& renderer, float deltatime)
{
	animInterval += deltatime;
	printf("%f", animInterval);
	if (animInterval >= animIntervalMax) {
		animInterval = 0.0f;
		animIndex++;
		if (animIndex >= objects.size())
			animIndex = 0;
	}
	Draw(renderer);
}

void SoloSprite::Draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(objects[animIndex], this->Position, this->Size);
}
