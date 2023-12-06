#include "Framework.h"

EffectManager::~EffectManager()
{
    for (pair<string, Effects> effects : totalEffect)
    {
        for (Effect* effect : effects.second)
            delete effect;
    }
}

void EffectManager::Update()
{
    for (pair<string, Effects> effects : totalEffect)
    {
        for (Effect* effect : effects.second)
            effect->Update();
    }
}

void EffectManager::Render()
{
    for (pair<string, Effects> effects : totalEffect)
    {
        for (Effect* effect : effects.second)
            effect->Render();
    }
}

void EffectManager::Add(string key, wstring textureFile, float maxFrameX, float maxFrameY, float speed, bool isAdditive)
{
    if (totalEffect.count(key) > 0)
        return;

    Effects effects(10);

    for (Effect*& effect : effects)
    {
        effect = new Effect(textureFile, Vector2(maxFrameX, maxFrameY), speed, isAdditive);
    }

    totalEffect[key] = effects;
}

void EffectManager::Add(string key, UINT poolSize, wstring textureFile, float maxFrameX, float maxFrameY, float speed, bool isAdditive)
{
    if (totalEffect.count(key) > 0)
        return;

    Effects effects(poolSize);

    for (Effect*& effect : effects)
    {
        effect = new Effect(textureFile, Vector2(maxFrameX, maxFrameY), speed, isAdditive);
    }

    totalEffect[key] = effects;
}

void EffectManager::Play(string key, Vector2 pos)
{
    if (totalEffect.count(key) == 0)
        return;

    for (Effect* effect : totalEffect[key])
    {
        if (!effect->Active())
        {
            effect->Play(pos);
            return;
        }
    }
}

void EffectManager::SetColor(string key, float r, float g, float b, float a)
{
    if (totalEffect.count(key) == 0)
        return;

    for (Effect* effect : totalEffect[key])
    {
        effect->GetColor() = { r, g, b, a };
    }
}
