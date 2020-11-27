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
	float obj_x;
	float obj_y;
public:
	CollObject *gameObject;
	float X;
	float Y;
	float Width;
	float Height;

	Collider();
	Collider(float x, float y, float w, float h);
	virtual ~Collider();

	void CreateBorder();
	void SetObjPos(float x, float y) { obj_x = x; obj_y = y; }
	void Draw(SpriteRenderer& renderer);
};