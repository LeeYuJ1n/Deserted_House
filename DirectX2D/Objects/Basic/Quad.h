#pragma once

class Quad : public GameObject
{
public:
    Quad(Vector2 size);
    Quad(wstring file, Vector2 startUV = Vector2(), Vector2 endUV = Vector2(1, 1));
    ~Quad();

    virtual void Render();
    
    void SetTexture(wstring file);
    void SetTexture(Texture* texture) { this->texture = texture; }

    Vector2 GetSize() { return size; }
    Vector2 Half() { return size * 0.5f; }

    Float4& GetColor() { return colorBuffer->Get(); }
    Texture* GetTexture() { return texture; }

private:
    void CreateMesh(Vector2 size, Vector2 startUV, Vector2 endUV);

protected:
    VertexBuffer* vertexBuffer = nullptr;
    IndexBuffer* indexBuffer = nullptr;
    ColorBuffer* colorBuffer = nullptr;

    Texture* texture = nullptr;

    vector<Vertex> vertices;
    vector<UINT> indices;

    Vector2 size;
};