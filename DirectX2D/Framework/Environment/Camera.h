#pragma once

class Camera : public Transform
{
public:
    Camera();
    ~Camera();

    void Update();
    void SetView();

    void SetTarget(Transform* target) { this->target = target; }

private:
    // 카메라의 시야 유형 설정
    void FollowMode(); // Follow-Cam : 카메라가 기준점이 있어서 기준의 위치에 상대 고정
    void FreeMode();   // Free-Cam   : 카메라가 기준이 없고 입력받은 대로 위치가 바뀐다

    //공간과 공간 버퍼
    MatrixBuffer* viewBuffer;
    Matrix view;

    float speed = 100.0f;

    Transform* target = nullptr; // 팔로우 캠 모드일 때 기준이 될 수 있는 표적 사물
};

