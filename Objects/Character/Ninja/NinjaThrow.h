#pragma once

class NinjaThrow : public Action
{
public:
    NinjaThrow(Transform* target);
    ~NinjaThrow() = default;

    virtual void End() override;

private:
    void Fire();

private:
    Transform* target;
};