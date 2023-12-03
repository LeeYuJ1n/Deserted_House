#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
    background = new Quad(L"Textures/Shooting/backgraound.png");
    background->Pos() = { CENTER_X, CENTER_Y };
    background->UpdateWorld();

    plane = new Plane();
    plane->Pos() = { CENTER_X, CENTER_Y };    
    plane->Scale() = { 0.5f, 0.5f };
}

TextureScene::~TextureScene()
{
    delete plane;
    delete background;
}

void TextureScene::Update()
{   
    plane->Update();
}

void TextureScene::Render()
{
    background->Render();

    plane->Render();
}

void TextureScene::PostRender()
{
    plane->RenderUI();
}
