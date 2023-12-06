#pragma once

class TextureScene : public Scene
{
public:
    TextureScene();
    ~TextureScene();
        
    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;

private:
    Plane* plane;
    Quad* background;
};