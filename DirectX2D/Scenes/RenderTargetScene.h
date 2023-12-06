#pragma once
class RenderTargetScene : public Scene
{
public:
    RenderTargetScene();
    ~RenderTargetScene();

    virtual void Update() override;
    virtual void Render() override;

    virtual void PreRender() override;
    virtual void PostRender() override;

private:
    Quad* background;
    Plane* plane;

    RenderTarget* renderTarget; //렌더 타겟 정보를 변수처럼 지정
    vector<Quad*> renderTextures;

    IntValueBuffer* intBuffer;
    FloatValueBuffer* floatBuffer;
};

