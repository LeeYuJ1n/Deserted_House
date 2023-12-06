#include "Framework.h"

Plane::Plane()
    : Quad(L"Textures/Shooting/airplane.png")
{
    tag = "Plane";

    turret = new Quad(L"Textures/Shooting/player.png");
    turret->SetParent(this);
    turret->Pos().x = 100.0f;

    BulletManager::Get();
}

Plane::~Plane()
{
    delete turret;

    BulletManager::Delete();
}

void Plane::Update()
{
    Move();
    Rotate();
    Fire();

    UpdateWorld();
    turret->UpdateWorld();

    BulletManager::Get()->Update();
}

void Plane::Render()
{
    Quad::Render();
    turret->Render();

    BulletManager::Get()->Render();
}

void Plane::Move()
{
    if (KEY_PRESS('W')) localPosition += Right() * speed * DELTA;
    if (KEY_PRESS('S')) localPosition -= Right() * speed * DELTA;
}

void Plane::Rotate()
{
    if (KEY_PRESS('A')) localRotation.z += DELTA;
    if (KEY_PRESS('D')) localRotation.z -= DELTA;

    if (KEY_PRESS('Q')) turret->Rot().z += DELTA;
    if (KEY_PRESS('E')) turret->Rot().z -= DELTA;
}

void Plane::Fire()
{
    if (KEY_DOWN(VK_LBUTTON))
    {
        BulletManager::Get()->Fire(turret->GlobalPos(), turret->Right());
    }
}
