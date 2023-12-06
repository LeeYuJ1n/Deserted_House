#pragma once

class Environment : public Singleton<Environment>
{
private:
    friend class Singleton;

    Environment();
    ~Environment();

public:
    void SetAlphaBlend();
    void SetAdditiveBlend();

    // Camera* GetMainCamera() { return mainCamera; }

private:
    void CreateProjection();
    void CreateSamplerState();
    void CreateBlendState();
    void CreateRasterizerState();

private:
    MatrixBuffer* projectionBuffer;

    ID3D11SamplerState* samplerState;
    ID3D11BlendState* alphaBlendState;
    ID3D11BlendState* additiveBlendState;
    ID3D11RasterizerState* rasterizerState;

    // Camera* mainCamera;
};