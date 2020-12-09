#pragma once
#include <glm/glm.hpp>
#include "player.h"

class Camera
{
public:
	static Player* player;

	static float startX;
	static float posX;
	static float prevX;

	Camera();
};