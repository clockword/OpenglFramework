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
public:
	glm::vec2   Position, Size;
	unsigned int Width;
	float MaxAniInterval;

	SoloSprite();
	~SoloSprite();

	void PushSprite(std::vector<Texture2D> sprites);
	void Update(SpriteRenderer& renderer, float deltatime);
protected:
	void Draw(SpriteRenderer& renderer);
};

