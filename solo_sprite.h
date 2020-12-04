#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "texture.h"
#include "sprite_renderer.h"

class SoloSprite
{
private:
	std::vector<Texture2D> objects;
	int animIndex;
	float animInterval;
	float animIntervalMax;
public:
	glm::vec2   Position, Size;
	unsigned int Width;

	SoloSprite();

	void PushSprite();
	void Update(SpriteRenderer& renderer, float deltatime);
protected:
	void Draw(SpriteRenderer& renderer);
};

