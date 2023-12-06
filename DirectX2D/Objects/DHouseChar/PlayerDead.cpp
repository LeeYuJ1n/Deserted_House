#include "Framework.h"

PlayerDead::PlayerDead(Transform* target)
	: Action("Textures/DHouseTexure/Player/", "Player_Dead.xml", false), target(target)
{

}

void PlayerDead::Update()
{
	Control();

	Action::Update();
}

void PlayerDead::Control()
{
	if (KEY_DOWN('K')) {}
}

