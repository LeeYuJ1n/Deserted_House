#pragma once

class NinjaGlide : public NinjaJump
{
public:
    NinjaGlide(Transform* target);
    ~NinjaGlide() = default;

    virtual void Update() override;
};