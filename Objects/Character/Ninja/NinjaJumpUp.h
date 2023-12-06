#pragma once

class NinjaJumpUp : public NinjaJump
{
private:
    const float JUMP_POWER = 1000.0f;

public:
    NinjaJumpUp(Transform* target);
    ~NinjaJumpUp() = default;

    virtual void Update() override;
    virtual void Start() override;
};