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

	void Init();
	void Update(SpriteRenderer& renderer, float deltatime);
	void FixedUpdate(float deltatime);
	void ClearSingletonObjects();
	void CreateLevel(std::string file);
	void ClearLevel();
};

