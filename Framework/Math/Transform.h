#pragma once

class Transform
{
public:
    Transform();
    ~Transform() = default;

    void UpdateWorld();
    void RenderUI();
    
    Vector2 Right() { return right.GetNormalized(); }
    Vector2 Left() { return right.GetNormalized() * -1.0f; }
    Vector2 Up() { return up.GetNormalized(); }
    Vector2 Down() { return up.GetNormalized() * -1.0f; }

    Vector2 GlobalPos() { return globalPosition; }
    Vector2 GlobalScale() { return globalScale; }

    void SetParent(Transform* transform) { parent = transform; }
    void SetPivot(Vector2 pivot) { this->pivot = pivot; }

    Transform* transform = this;

    bool Active();
    bool ActiveSelf() { return isActive; }

    void SetActive(bool isActive) { this->isActive = isActive; }

    void SetTag(string tag) { this->tag = tag; }

    Vector2& Pos() { return localPosition; }
    Float3& Rot() { return localRotation; }
    Vector2& Scale() { return localScale; }

    void Save();
    void Load(); // 기존에 (파일로) 저장된 트랜스폼 정보가 있었을 경우, 불러오기
    Transform* GetParent() { return parent; }

protected:
    string tag;

    Vector2 localPosition;
    Float3 localRotation = { 0, 0, 0 };
    Vector2 localScale = { 1, 1 };

    bool isActive = true;    

    Matrix world;

private:
    Transform* parent = nullptr;

    Matrix S, R, T;
    Matrix P, IP;
    Vector2 pivot;

    Vector2 right, up;
    Vector2 globalPosition, globalScale;

    XMFLOAT4X4 matWorld;
    
};