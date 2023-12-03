#include "Framework.h"
#include "ShaderScene.h"

ShaderScene::ShaderScene()
{
    Init();
}

ShaderScene::~ShaderScene()
{
    Quit();
}

void ShaderScene::Init()
{
    quad = new Quad(L"Textures/shibe.jpg");
    quad->Pos() = { CENTER_X, CENTER_Y };
    quad->UpdateWorld();

    quad->SetPixelShader(L"Multi.hlsl");
    //quad->SetPixelShader(L"Light.hlsl");
    //quad->SetPixelShader(L"Filter.hlsl");

    intValueBuffer = new IntValueBuffer();
    floatValueBuffer = new FloatValueBuffer();
    floatValueBuffer->Get()[0] = quad->GetSize().x;
    floatValueBuffer->Get()[1] = quad->GetSize().y;

    secondMap = Texture::Add(L"Textures/sun.png");
}

void ShaderScene::Quit()
{
    delete quad;
    delete intValueBuffer;
    delete floatValueBuffer;
}

void ShaderScene::Update()
{
}

void ShaderScene::Render()
{
    secondMap->PSSet(1);

    intValueBuffer->SetPS(1);
    floatValueBuffer->SetPS(2);

    quad->Render();
}

void ShaderScene::PostRender()
{
    ImGui::ColorEdit4("Color", (float*)&quad->GetColor());
    ImGui::SliderInt("Index", intValueBuffer->Get(), 0, 8);
    ImGui::SliderInt("Scale", &intValueBuffer->Get()[1], 0, 100);
    ImGui::SliderInt("Scale1", &intValueBuffer->Get()[2], 0, 100);
    ImGui::SliderInt("Scale2", &intValueBuffer->Get()[3], 0, 100);
    ImGui::SliderFloat2("LightPos", &floatValueBuffer->Get()[2], 0, 1000);
}
