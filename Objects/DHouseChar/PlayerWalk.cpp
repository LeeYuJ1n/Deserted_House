#include "Framework.h"

PlayerWalk::PlayerWalk(Transform* target)
	: Action("Textures/DHouseTexure/Player/", "Player_Walk.xml", true), target(target)
{
    
}

void PlayerWalk::Update()
{
	Control();

	// target->Pos().x += velocity * MOVE_SPEED * DELTA;

	Action::Update();	
}

void PlayerWalk::SetPlayer(Player* target)
{
    player = target;
}

void PlayerWalk::Control()
{
    if (KEY_PRESS(VK_RIGHT))
    {
        target->Pos().x += moveSpeed;
        velocity = 1.0f;
        // target->Scale().x = 1;
        target->Rot().y = 0;
    }
    
    if (KEY_PRESS(VK_LEFT))
    {
        
        // Audio::Get()->Play("WalkSound", 10.0f);

        target->Pos().x -= moveSpeed;
        velocity = -1.0f;
        // target->Scale().x = -1;
        target->Rot().y = XM_PI;
    }
    
    if (KEY_PRESS(VK_UP))
    {
        // Audio::Get()->Play("WalkSound", 10.0f);

        target->Pos().y += moveSpeed;
    }

    if (KEY_PRESS(VK_DOWN))
    {
        // Audio::Get()->Play("WalkSound", 10.0f);

        target->Pos().y -= moveSpeed;
    }
}


