#pragma once
#include <string>
#include "sprite_renderer.h"
#include "level.h"

class Game
{
private:
	Level* level;
public:
	Game();
	~Game();

	void Init(const unsigned int scr_width, const unsigned int scr_height);
	void Update(SpriteRenderer& renderer, float deltatime);
	void FixedUpdate(float deltatime);
	void ClearSingletonObjects();
private:
	void CreateLevel(std::string file);
	void ClearLevel();
};

