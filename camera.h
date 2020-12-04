#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	static float startX;
	static float posX;

	Camera() { posX = 0.0f; }
};

float Camera::startX;
float Camera::posX;