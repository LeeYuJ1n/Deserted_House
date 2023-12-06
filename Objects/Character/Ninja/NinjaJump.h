#pragma once

class NinjaJump : public Action
{
public:
    NinjaJump(Transform* target);
    ~NinjaJump() = default;

    virtual void Update() override;    

protected:
    void Move();

protected:
    Transform* target;

    float velocity = 0.0f;    
};