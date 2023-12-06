#include "Framework.h"

NinjaRun::NinjaRun(Transform* target)
    : Action("Textures/Ninja/", "Ninja_Run.xml", true), target(target)
{
}

void NinjaRun::Update()
{
    Control();

    target->Pos().x += velocity * MOVE_SPEED * DELTA;

    Action::Update();
}

void NinjaRun::Control()
{
    if (KEY_PRESS(VK_RIGHT))
    {
        velocity = 1.0f;
        //target->Scale().x = 1;
        target->Rot().y = 0;
    }

    if (KEY_PRESS(VK_LEFT))
    {
        velocity = -1.0f;
        //target->Scale().x = -1;
        target->Rot().y = XM_PI;
    }
}
