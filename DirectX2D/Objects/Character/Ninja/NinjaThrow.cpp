#include "Framework.h"

NinjaThrow::NinjaThrow(Transform* target)
    : Action("Textures/Ninja/", "Ninja_Throw.xml", true), target(target)
{
    clip->SetEvent(bind(&NinjaThrow::Fire, this), 8);
    clip->SetEvent(bind(&NinjaThrow::End, this));
}

void NinjaThrow::End()
{
    event();
}

void NinjaThrow::Fire()
{
    Vector2 firePos = target->Pos() + target->Right() * 20.0f;

    BulletManager::Get()->Fire(firePos, target->Right());
}
