#pragma once

class Scene
{
public:
    virtual ~Scene() = default;

    //필수
    virtual void Update() = 0;    
    virtual void Render() = 0;

    //옵션
    virtual void Init() {}
    virtual void Quit() {}

    virtual void PreRender() {}
    virtual void PostRender() {}
};