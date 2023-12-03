#pragma once

class Plane : public Quad
{
public:
    Plane();
    ~Plane();

    void Update();  
    void Render();
    
private:
    void Move();
    void Rotate();
    void Fire();

private:
    float speed = 200.0f;

    Quad* turret;
};