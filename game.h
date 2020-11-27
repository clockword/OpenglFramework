#pragma once
#include "sprite_renderer.h"

class Game
{
public:
	Game() {}
	~Game() {}

	void Init(const unsigned int scr_width, const unsigned int scr_height);
	void Update(SpriteRenderer& renderer, float deltatime);
	void FixedUpdate(float deltatime);
	void Clear();
};

