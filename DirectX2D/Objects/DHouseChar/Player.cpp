#include "Framework.h"

Player::Player()
{
    SetPixelShader(L"Ninja.hlsl");

    CreateActions();
    actions[curAction]->Start();

    Observer::Get()->AddIntParamEvent("Action",
        bind(&Player::SetAction, this, placeholders::_1));

    // sLayer = Texture::Add(L"Textures/yellow.png");

    intValueBuffer = new IntValueBuffer();
    floatValueBuffer = new FloatValueBuffer();
    characterArea = new RectCollider(Vector2(30, 100));
    characterArea->SetParent(this);
}

Player::~Player()
{
    for (pair<ActionType, Action*> action : actions)
        delete action.second;
}

void Player::Update()
{
    Control();

    actions[curAction]->Update();
    UpdateWorld();

    characterArea->UpdateWorld();

    Vector2 size = actions[curAction]->GetClip()->GetCurFrame()->GetSize();
    floatValueBuffer->Get()[0] = size.x;
    floatValueBuffer->Get()[1] = size.y;
    BlockObject(BlockList);
}

void Player::Render()
{
    // sLayer->PSSet(1);

    intValueBuffer->SetPS(1);
    floatValueBuffer->SetPS(2);

    SetRender();

    actions[curAction]->Render();
    // characterArea->Render();
}

void Player::AddBlockObject(RectCollider* coll)
{
    BlockList.push_back(coll);
}

void Player::Control()
{
    Move();
}

void Player::Move()
{
    bool isMove = false;

    isMove |= KEY_PRESS(VK_RIGHT);
    isMove |= KEY_PRESS(VK_LEFT);
    isMove |= KEY_PRESS(VK_UP);
    isMove |= KEY_PRESS(VK_DOWN);

    isMove ? SetAction(WALK) : SetAction(IDLE);
}

void Player::SetIdle()
{
    SetAction(IDLE);
}

void Player::SetAction(int type)
{
    if (curAction == type) return;

    curAction = (ActionType)type;
    actions[(ActionType)type]->Start();
}

void Player::CreateActions()
{
    actions[IDLE] = new Action("Textures/DHouseTexure/Player/", "Player_Idle.xml", true);
    actions[WALK] = new PlayerWalk(this);
    actions[DEAD] = new PlayerDead(this);
}

void Player::BlockObject(vector<RectCollider*> collList)
{
    for (RectCollider* coll : collList)
    {
        if (coll->R() >= characterArea->L() &&
            coll->B() <= characterArea->T() &&
            coll->T() >= characterArea->B() &&
            coll->R() <= characterArea->R())
        {
            this->Pos().x += 5.0f;
        }

        // Left collision
        if (coll->L() <= characterArea->R() &&
            coll->B() <= characterArea->T() &&
            coll->T() >= characterArea->B() &&
            coll->L() >= characterArea->L())
        {
            this->Pos().x -= 5.0f;
        }

        // Top collision
        if (coll->T() >= characterArea->B() &&
            coll->L() <= characterArea->R() &&
            coll->R() >= characterArea->L() &&
            coll->T() <= characterArea->T())
        {
            this->Pos().y += 5.0f;
        }

        // Bottom collision
        if (coll->B() <= characterArea->T() &&
            coll->L() <= characterArea->R() &&
            coll->R() >= characterArea->L() &&
            coll->B() >= characterArea->B())
        {
            this->Pos().y -= 5.0f;
        }
    }
}