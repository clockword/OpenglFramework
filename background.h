#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "solo_sprite.h"
#include "sprite_renderer.h"

class Background
{
protected:
    int size;
    SoloSprite* objects;
public:
    bool IsMoving;

    Background();
    ~Background();

    void PushSprite(std::vector<Texture2D> sprites, glm::vec2 scale = glm::vec2(1.0f, 1.0f), float speed = 1.0f, float maxAniInterval = 0.2f);
    void Update(SpriteRenderer& renderer, float deltatime);
};

