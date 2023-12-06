#pragma once

class Ninja : public GameObject
{
private:
    enum ActionType
    {
        IDLE = 0, RUN,
        JUMP_UP, JUMP_DOWN, GLIDE,
        ATTACK = 10,
        JUMP_ATTACK, THROW, JUMP_THROW,
        DEAD, SLIDE, 
    };

public:
    Ninja();
    ~Ninja();

    void Update();
    void Render();
    void PostRender();

private:
    void Control();

    void Move();
    void Jump();
    void Attack();
    void Glide();

    void SetIdle();
    void Fall();

    void SetAction(int type);

    void CreateActions();    

private:
    map<ActionType, Action*> actions;

    ActionType curAction = JUMP_DOWN;

    Texture* sLayer;

    IntValueBuffer* intValueBuffer;
    FloatValueBuffer* floatValueBuffer;
};