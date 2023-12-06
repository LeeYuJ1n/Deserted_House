#pragma once

class NinjaJumpDown : public NinjaJump
{
private:
    const float JUMP_POWER = 500.0f;

public:
    NinjaJumpDown(Transform* target);
    ~NinjaJumpDown() = default;

    virtual void Update() override;
    virtual void Start() override;
};