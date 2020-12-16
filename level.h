#pragma once
#include <map>
#include <string>
#include "game_object.h"
#include "background.h"
#include "sprite_renderer.h"

class Level
{
private:
	Background back;
	Background vBack;
	Background front;
	std::map<int, GameObject*> objects;
public:
	std::string name;
	bool IsCleared;
	unsigned int scrWidth;
	unsigned int scrHeight;

	Level();
	virtual ~Level();

	void Init();
	void Create(std::string filename);
	void Update(SpriteRenderer& renderer, float deltatime);
	void FixedUpdate(float deltatime);
	void Clear();
};

