#include "Framework.h"

Tank::Tank() : Quad(L"Textures/Shooting/Tank_Body.png")
{
    collider = new RectCollider(texture->GetSize());
    collider->SetTag("TankCollider");
    collider->Load();
    collider->SetParent(this);

    head = new Quad(L"Textures/Shooting/Tank_Head.png");
    head->SetParent(this);    
}

Tank::~Tank()
{
    delete collider;
    delete head;
}

void Tank::Update()
{
    //Control();
    HeadControl();
    MovePath();

    UpdateWorld();
    collider->UpdateWorld();
    head->UpdateWorld();
}

void Tank::Render()
{
    Quad::Render();
    head->Render();

    collider->Render();
}

void Tank::PostRender()
{
    collider->RenderUI();
}

void Tank::Control()
{
    if (KEY_PRESS('W'))
        Pos() += Right() * moveSpeed * DELTA;

    if (KEY_PRESS('S'))
        Pos() -= Right() * moveSpeed * DELTA;

    if (KEY_PRESS('A'))
        Rot().z += rotSpeed * DELTA;

    if (KEY_PRESS('D'))
        Rot().z -= rotSpeed * DELTA;
}

void Tank::HeadControl()
{
    Vector2 direction = mousePos - head->GlobalPos();
    head->Rot().z = direction.Angle() - Rot().z;
}

void Tank::MovePath()
{
    if (path.empty())
        return;

    Vector2 direction = path.back() - Pos();
    Rot().z = direction.Angle();

    Pos() += Right() * moveSpeed * DELTA;
    
    if (direction.Length() < 5.0f)
        path.pop_back();
}
