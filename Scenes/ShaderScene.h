#pragma once

class ShaderScene : public Scene
{
public:
    ShaderScene();
    ~ShaderScene();

    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;

    virtual void Init() override;
    virtual void Quit() override;

private:
    Quad* quad;
    Texture* secondMap;
    IntValueBuffer* intValueBuffer;
    FloatValueBuffer* floatValueBuffer;
};