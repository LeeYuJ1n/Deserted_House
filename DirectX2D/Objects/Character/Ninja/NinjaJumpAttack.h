#pragma once

class NinjaJumpAttack : public NinjaAttack
{
public:
    NinjaJumpAttack(Transform* target);
    ~NinjaJumpAttack() = default;

    virtual void Update() override;    
};