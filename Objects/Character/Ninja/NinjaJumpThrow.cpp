#include "Framework.h"

NinjaJumpThrow::NinjaJumpThrow(Transform* target)
    : Action("Textures/Ninja/", "Ninja_JumpThrow.xml", true), target(target)
{
    clip->SetEvent(bind(&NinjaJumpThrow::Fire, this), 8);
    clip->SetEvent(bind(&NinjaJumpThrow::End, this));
}

void NinjaJumpThrow::End()
{
    event();
}

void NinjaJumpThrow::Fire()
{
    Vector2 firePos = target->Pos() + target->Right() * 20.0f;

    BulletManager::Get()->Fire(firePos, target->Right());
}
