#pragma once

class Collider : public Transform
{
protected:
    enum class Type
    {
        RECT, CIRCLE
    };

    const float PUSH_SPEED = 500.0f;

public:
    Collider();
    ~Collider();

    void Render();

    bool IsCollision(Collider* collider);

    virtual bool IsPointCollision(Vector2 point) = 0;
    virtual bool IsRectCollision(class RectCollider* rect, Vector2* overlap = nullptr) = 0;
    virtual bool IsCircleCollision(class CircleCollider* circle) = 0;

    virtual bool PushCollider(Collider* collider) = 0;

    Float4& GetColor() { return colorBuffer->Get(); }

protected:
    Type type;

    VertexBuffer* vertexBuffer;
    vector<VertexPos> vertices;

private:
    VertexShader* vertexShader;
    PixelShader* pixelShader;

    MatrixBuffer* worldBuffer;
    ColorBuffer* colorBuffer;
};