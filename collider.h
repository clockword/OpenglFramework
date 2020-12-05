#pragma once
#include <string>
#include "texture.h"
#include "sprite_renderer.h"
#include "coll_object.h"

class CollObject;
class Collider
{
private:
	Texture2D colorBorder;
public:
	CollObject *gameObject;
	float CollX;
	float CollY;
	float X;
	float Y;
	float Width;
	float Height;

	Collider();
	Collider(float x, float y, float w, float h);
	virtual ~Collider();

	void CreateBorder();
	void SetPos(float x, float y) { X = x; Y = y; }
	void Draw(SpriteRenderer& renderer);
};