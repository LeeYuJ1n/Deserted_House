#pragma once

class EffectManager : public Singleton<EffectManager>
{
private:
    friend class Singleton;

    EffectManager() = default;
    ~EffectManager();
    
public:
    void Update();
    void Render();

    void Add(string key, wstring textureFile,
        float maxFrameX, float maxFrameY, float speed = 1.0f, bool isAdditive = false);

    void Add(string key, UINT poolSize, wstring textureFile,
        float maxFrameX, float maxFrameY, float speed = 1.0f, bool isAdditive = false);

    void Play(string key, Vector2 pos);
    void SetColor(string key, float r, float g, float b, float a = 1.0f);

private:
    typedef vector<Effect*> Effects;
    unordered_map<string, Effects> totalEffect;
};