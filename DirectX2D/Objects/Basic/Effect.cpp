#include "Framework.h"

Effect::Effect(wstring textureFile, Vector2 maxFrame, float speed, bool isAdditive)
    : Quad(textureFile, Vector2(), Vector2(1/ maxFrame.x, 1/ maxFrame.y)),
        speed(speed), isAdditive(isAdditive)
{
    pixelShader = Shader::AddPS(L"PixelEffect.hlsl");

    isActive = false;
    
    frameBuffer = new FrameBuffer();
    frameBuffer->SetMaxFrame(maxFrame);

    maxFrameNum = (UINT)(maxFrame.x * maxFrame.y);
    maxFrameX = (UINT)maxFrame.x;
}

Effect::~Effect()
{
    delete frameBuffer;
}

void Effect::Update()
{
    if (!isActive) return;

    frameTime += speed * DELTA;

    if (frameTime >= delayTime)
    {
        frameTime -= delayTime;

        curFrameNum++;

        frameBuffer->GetCurFrame().x = (float)(curFrameNum % maxFrameX);
        frameBuffer->GetCurFrame().y = (float)(curFrameNum / maxFrameX);        

        if (curFrameNum >= maxFrameNum)
            End();
    }

    UpdateWorld();
}

void Effect::Render()
{
    if (!isActive) return;

    if (isAdditive)
        Environment::Get()->SetAdditiveBlend();

    frameBuffer->SetPS(1);
    Quad::Render();

    Environment::Get()->SetAlphaBlend();
}

void Effect::Play(Vector2 position)
{
    isActive = true;
    Pos() = position;

    frameTime = 0.0f;
    curFrameNum = 0;

    frameBuffer->GetCurFrame() = { 0, 0 };
}

void Effect::End()
{
    isActive = false;
}
