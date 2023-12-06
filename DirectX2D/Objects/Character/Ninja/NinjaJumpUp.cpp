#include "Framework.h"

NinjaJumpUp::NinjaJumpUp(Transform* target)
    : NinjaJump(target)
{
    wstring file = L"Textures/Ninja/Ninja_Jump.png";
    Texture* texture = Texture::Add(file);
    Vector2 cutSize = texture->GetSize() / Vector2(1, 10);

    vector<Frame*> frames;
    frames.push_back(new Frame(file, 0, cutSize.y * 0, cutSize.x, cutSize.y));
    frames.push_back(new Frame(file, 0, cutSize.y * 1, cutSize.x, cutSize.y));
    frames.push_back(new Frame(file, 0, cutSize.y * 2, cutSize.x, cutSize.y));
    frames.push_back(new Frame(file, 0, cutSize.y * 3, cutSize.x, cutSize.y));
    frames.push_back(new Frame(file, 0, cutSize.y * 4, cutSize.x, cutSize.y));
    frames.push_back(new Frame(file, 0, cutSize.y * 5, cutSize.x, cutSize.y));

    clip = new Clip(frames, false);
}

void NinjaJumpUp::Update()
{
    NinjaJump::Update();

    if (velocity <= 0.0f)
        event();
}

void NinjaJumpUp::Start()
{
    Action::Start();

    velocity = JUMP_POWER;
}
