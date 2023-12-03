#include "Framework.h"

Bullet::Bullet()
    : Quad(L"Textures/Shooting/playerBullet2.png")
{
    isActive = false;

    localScale = { 0.5f, 0.5f };
    collider = new RectCollider(texture->GetSize());
    collider->SetParent(this);
}

Bullet::~Bullet()
{
    delete collider;
}

void Bullet::Update()
{
    if (!isActive) return;

    localPosition += direction * speed * DELTA;

    if (localPosition.x < 0 || localPosition.x > WIN_WIDTH)
        isActive = false;

    if (localPosition.y < 0 || localPosition.y > WIN_HEIGHT)
        isActive = false;
        
    UpdateWorld();
    collider->UpdateWorld();
}

void Bullet::Render()
{
    if (!isActive) return;

    Quad::Render();

    collider->Render();
}

void Bullet::Fire(Vector2 pos, Vector2 direction)
{
    isActive = true;

    localPosition = pos;
    this->direction = direction;

    localRotation.z = direction.Angle();
}
