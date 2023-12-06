#pragma once

class Tank : public Quad
{
public:
    Tank();
    ~Tank();

    void Update();
    void Render();
    void PostRender();

    RectCollider* GetCollider() { return collider; }

    void SetPath(vector<Vector2> path) { this->path = path; }
    vector<Vector2>& GetPath() { return path; }

private:
    void Control();
    void HeadControl();

    void MovePath();

private:
    float moveSpeed = 200.0f;
    float rotSpeed = 5.0f;

    RectCollider* collider;

    Quad* head;

    vector<Vector2> path;
};