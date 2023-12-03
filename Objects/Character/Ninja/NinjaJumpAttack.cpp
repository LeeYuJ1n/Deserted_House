#include "Framework.h"

NinjaJumpAttack::NinjaJumpAttack(Transform* target)
    : NinjaAttack("Ninja_JumpAttack.xml", target)
{
    power = 100.0f;

    attackCollider = new RectCollider(Vector2(70, 120));
    attackCollider->Pos().x = 50.0f;
    attackCollider->SetParent(target);
    attackCollider->SetActive(false);

    clip->SetEvent(bind(&NinjaAttack::EnableCollider, this), 4);
    clip->SetEvent(bind(&NinjaJumpAttack::DisableCollider, this), 7);
}

void NinjaJumpAttack::Update()
{
    Action::Update();   
}