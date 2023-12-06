#pragma once
#include "Framework.h"

class Wall : public GameObject
{
public:
    Wall(Vector2 size);
    ~Wall();

    void Update();
    void Render();

    RectCollider* wall;
};

