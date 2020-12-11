#include "solo_sprite.h"
#include "resource_manager.h"

SoloSprite::SoloSprite()
{
	animIndex = 0;
	animInterval = 0.0f;
	MaxAniInterval = 0.2f;
	Position = glm::vec2(0.0f, 0.0f);
	Size = glm::vec2(1.0f, 1.0f);
	Width = 0;
	Speed = 0.0f;
}

SoloSprite::~SoloSprite()
{
}

void SoloSprite::PushSprite(std::vector<Texture2D> sprites)
{
	objects = sprites;
	Width = sprites[0].Width;
}

void SoloSprite::Update(SpriteRenderer& renderer, float deltatime)
{
	animInterval += deltatime;
	if (animInterval >= MaxAniInterval) {
		animInterval = 0.0f;
		animIndex++;
		if (animIndex >= objects.size())
			animIndex = 0;
	}
	Draw(renderer);
}

void SoloSprite::Draw(SpriteRenderer& renderer)
{
	glm::vec2 pos(this->Position);

	renderer.DrawSprite(objects[animIndex], pos, this->Size);
}
