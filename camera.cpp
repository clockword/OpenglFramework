#include "camera.h"

Player* Camera::player;
float Camera::startX;
float Camera::posX;
float Camera::prevX;

Camera::Camera()
{
	startX = 0.0f;
	posX = 0.0f;
	prevX = 0.0f;
}
