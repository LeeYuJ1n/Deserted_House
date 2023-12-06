#include "Framework.h"

NinjaGlide::NinjaGlide(Transform* target)
    : NinjaJump(target)
{
    LoadClip("Textures/Ninja/", "Ninja_Glide.xml", false, 1.0f);

    velocity = 10.0f;
}

void NinjaGlide::Update()
{
    target->Pos().y -= velocity * DELTA;

    Move();

    Action::Update();
}