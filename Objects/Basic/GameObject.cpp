#include "Framework.h"

GameObject::GameObject(wstring shaderFile)
{
    vertexShader = Shader::AddVS(L"Vertex" + shaderFile);
    pixelShader = Shader::AddPS(L"Pixel" + shaderFile);

    worldBuffer = new MatrixBuffer();
}

GameObject::~GameObject()
{ 
    delete worldBuffer;
}

void GameObject::SetRender()
{   
    worldBuffer->Set(world);
    worldBuffer->SetVS(0);    

    vertexShader->Set();
    pixelShader->Set();    
}

void GameObject::SetPixelShader(wstring shaderFile)
{
    pixelShader = Shader::AddPS(L"Pixel" + shaderFile);
}
