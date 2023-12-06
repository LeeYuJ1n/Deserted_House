#include "Framework.h"

unordered_map<wstring, Shader*> Shader::shaders;

Shader::~Shader()
{
    blob->Release();
}

VertexShader* Shader::AddVS(wstring file)
{    
    if (shaders.count(file) > 0)
        return (VertexShader*)shaders[file];

    wstring path = L"Shaders/" + file;
    shaders[file] = new VertexShader(path);

    return (VertexShader*)shaders[file];
}

PixelShader* Shader::AddPS(wstring file)
{
    if (shaders.count(file) > 0)
        return (PixelShader*)shaders[file];

    wstring path = L"Shaders/" + file;
    shaders[file] = new PixelShader(path);

    return (PixelShader*)shaders[file];
}

void Shader::Delete()
{
    for (pair<wstring, Shader*> shader : shaders)
        delete shader.second;
}
