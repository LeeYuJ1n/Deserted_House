#include "Framework.h"
#include "Wall.h"

Wall::Wall(Vector2 size)
{
	wall = new RectCollider(size);
	wall->SetParent(this);
}

Wall::~Wall()
{
	delete wall;
}

void Wall::Update()
{
	UpdateWorld();
	wall->UpdateWorld();
}

void Wall::Render()
{
	wall->Render();
}
