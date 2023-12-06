#include "Framework.h"

NinjaMeleeAttack::NinjaMeleeAttack(Transform* target)
    : NinjaAttack("Ninja_Attack.xml", target)
{
    power = 100.0f;

    attackCollider = new RectCollider(Vector2(70, 120));
    attackCollider->Pos().x = 50.0f;
    attackCollider->SetParent(target);
    attackCollider->SetActive(false);

    clip->SetEvent(bind(&NinjaAttack::EnableCollider, this), 4);
    clip->SetEvent(bind(&NinjaAttack::DisableCollider, this), 7);    
}
