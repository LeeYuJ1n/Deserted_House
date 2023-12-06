#pragma once

class NinjaMeleeAttack : public NinjaAttack
{
public:
    NinjaMeleeAttack(Transform* target);
    ~NinjaMeleeAttack() = default;
};