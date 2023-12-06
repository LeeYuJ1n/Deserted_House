#include "Framework.h"

NinjaJump::NinjaJump(Transform* target)
    : target(target)
{
}

void NinjaJump::Update()
{
    velocity -= GRAVITY * DELTA;

    target->Pos().y += velocity * DELTA;

    Move();

    Action::Update();
}

void NinjaJump::Move()
{
    if (KEY_PRESS(VK_RIGHT))
    {
        target->Pos().x += MOVE_SPEED * DELTA;
        target->Rot().y = 0;
    }

    if (KEY_PRESS(VK_LEFT))
    {
        target->Pos().x -= MOVE_SPEED * DELTA;
        target->Rot().y = XM_PI;
    }
}
