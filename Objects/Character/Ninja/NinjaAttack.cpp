#include "Framework.h"

NinjaAttack::NinjaAttack(string file, Transform* target)
    : Action("Textures/Ninja/", file, false), target(target)
{    
    clip->SetEvent(bind(&NinjaAttack::End, this));
}

NinjaAttack::~NinjaAttack()
{
    delete attackCollider;
}

void NinjaAttack::Render()
{
    Action::Render();

    attackCollider->Render();
}

void NinjaAttack::End()
{
    event();
}

void NinjaAttack::EnableCollider()
{
    attackCollider->UpdateWorld();
    attackCollider->SetActive(true);
}

void NinjaAttack::DisableCollider()
{
    attackCollider->SetActive(false);
}
