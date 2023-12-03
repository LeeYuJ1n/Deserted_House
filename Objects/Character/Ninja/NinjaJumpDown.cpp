#include "Framework.h"

NinjaJumpDown::NinjaJumpDown(Transform* target)
    : NinjaJump(target)
{
    wstring file = L"Textures/Ninja/Ninja_Jump.png";
    Texture* texture = Texture::Add(file);
    Vector2 cutSize = texture->GetSize() / Vector2(1, 10);

    vector<Frame*> frames;
    frames.push_back(new Frame(file, 0, cutSize.y * 6, cutSize.x, cutSize.y));
    frames.push_back(new Frame(file, 0, cutSize.y * 7, cutSize.x, cutSize.y));
    frames.push_back(new Frame(file, 0, cutSize.y * 8, cutSize.x, cutSize.y));
    frames.push_back(new Frame(file, 0, cutSize.y * 9, cutSize.x, cutSize.y));

    clip = new Clip(frames, false);
}

void NinjaJumpDown::Update()
{
    NinjaJump::Update();

    if (target->Pos().y < FLOOR_HEIGHT)
    {
        target->Pos().y = FLOOR_HEIGHT;
        velocity = 0.0f;

        event();
    }    
}

void NinjaJumpDown::Start()
{
    Action::Start();

    velocity = 0.0f;
}
