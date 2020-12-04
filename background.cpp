#include "background.h"

#include "resource_manager.h"

Background::Background()
{
    size = 0;
    objects = nullptr;
    IsMoving = false;
}

Background::~Background()
{
    if (objects != nullptr && size == 1)
        delete objects;
    else if (objects != nullptr && size != 1)
        delete[] objects;
}

void Background::PushSprite(std::vector<Texture2D> sprites, glm::vec2 scale, float maxAniInterval)
{
    if (objects != nullptr)
    {
        SoloSprite* temp = new SoloSprite[size];
        for (int i = 0; i < size; ++i)
            temp[i] = objects[i];
        delete[] objects;
        size += 2;
        objects = new SoloSprite[size];
        for (int i = 0; i < size - 2; ++i)
            objects[i] = temp[i];
        objects[size - 2].PushSprite(sprites);
        objects[size - 1].PushSprite(sprites);
        objects[size - 2].Size = scale;
        objects[size - 1].Size = scale;
        objects[size - 2].MaxAniInterval = maxAniInterval;
        objects[size - 1].MaxAniInterval = maxAniInterval;
        objects[size - 1].Position.x = objects[size - 2].Position.x + objects[size - 2].Width * scale.x;
        delete[] temp;
    }
    else
    {
        objects = new SoloSprite[2];
        objects[0].PushSprite(sprites);
        objects[1].PushSprite(sprites);
        objects[0].Size = scale;
        objects[1].Size = scale;
        objects[0].MaxAniInterval = maxAniInterval;
        objects[1].MaxAniInterval = maxAniInterval;
        objects[1].Position.x = objects[0].Position.x + objects[0].Width * scale.x;
        size += 2;
    }
    
}

void Background::Update(SpriteRenderer& renderer, float deltatime)
{
    if (IsMoving)
    {
        for (int i = 0; i < size; ++i)
        {
            int width = objects[i].Width * objects[i].Size.x;
            int partner = i % 2 ? i - 1 : i + 1;
            if (objects[i].Position.x < -width)
                objects[i].Position.x = objects[partner].Position.x + width;
            else if (objects[i].Position.x > width)
                objects[i].Position.x = objects[partner].Position.x - width;
            int num = i + 2;
            objects[i].Position.x += (num % 2 ? num - 1 : num) * deltatime * 50.0f;
            objects[i].Update(renderer, deltatime);
        }
    }
    else
    {
        for (int i = 0; i < size; ++i)
            objects[i].Update(renderer, deltatime);
    }
}
