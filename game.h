#pragma once
#include <string>
#include "sprite_renderer.h"
#include "level.h"
#include "include/irrKlang/irrKlang.h"
#pragma comment(lib, "irrKlang.lib")

class Game
{
private:
	Level* level;
	unsigned int scrWidth;
	unsigned int scrHeight;
	irrklang::ISoundEngine* soundEngine;
	float overInterval;
	float overMax;
public:
	bool isOver;

	Game();
	~Game();

	void Init(unsigned int scr_width, unsigned int scr_height);
	void Update(SpriteRenderer& renderer, float deltatime);
	void FixedUpdate(float deltatime);
	void ClearSingletonObjects();
	void CreateLevel(std::string file);
	void ClearLevel();
};

