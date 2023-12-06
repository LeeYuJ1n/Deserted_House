#pragma once

class NinjaJumpThrow : public Action
{
public:
    NinjaJumpThrow(Transform* target);
    ~NinjaJumpThrow() = default;

    virtual void End() override;

private:
    void Fire();

private:
    Transform* target;
};