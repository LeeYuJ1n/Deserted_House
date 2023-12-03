#include "Framework.h"

// 카메라 원리 : 독립된 공간을 가진 트랜스폼을 만들어서, 그 위치가 뷰포트의 대상이 되도록
// 기본은 winAPI 때와 비슷 : 차이는 카메라가(카메라를 통해) 출력하는 것이 아니라
//                          출력은 똑같이 뷰포트가 하는 것뿐 (단지 참조 위치가 달라진다)

//                         -> 따라서, 만든 카메라를 바로 매니저에 띄워야 하거나 자동으로 쓰이는 것이 아니라
//                            Environment에서 설정을 해줘야 한다 (그러면 Environment가 반쯤 자동으로 출력)

Camera::Camera()
{
    //공간 버퍼
    viewBuffer = new MatrixBuffer();
    viewBuffer->SetPS(1);
    // 1 : 0 아님, 2 아님 = "게임의 공간"과는 구분된다
    // ui와는 같다 = VS는 다를 수 있어도 (공간 처리는 다를 수 있어도) 기타 셰이더, 출력 사항은 일부 공유할 수도...

    tag = "Camera"; // 나중에 객체관리가 (통합이든 분리든) 필요한 경우 태그로도 구분할 수 있도록
}

Camera::~Camera()
{
    delete viewBuffer;
    // 표적도 지우면 좋지만, 어차피 다른 곳에서 관리되고 있(거나 게임에서 마지막으로 지워져야 하)는 경우가 99%
}

void Camera::Update()
{
    // 기준점이 있으면 팔로우캠으로 동작, 아니면 프리캠으로 동작
    if (target != nullptr) FollowMode();
    else FreeMode();

    //뷰 세팅 (어디를 볼 것인가?)
    SetView();
}

void Camera::SetView()
{
    UpdateWorld(); // 트랜스폼으로서의 내용 업데이트 (카메라는 어디에 어떻게 있는가)

    view = XMMatrixInverse(nullptr, world);

    viewBuffer->Set(view);
    viewBuffer->SetVS(1); //공간 내용부터 만들고 그 다음에 정점 적용
}

void Camera::FollowMode()
{
    // TODO : 기준점이 생기고, 그 기준점의 행동 스타일이 정해지면 그때 작성
}

void Camera::FreeMode()
{
    // 카메라 자유 이동

    if (KEY_PRESS('T')) Pos().y += speed * DELTA;
    if (KEY_PRESS('G')) Pos().y -= speed * DELTA;
    if (KEY_PRESS('F')) Pos().x -= speed * DELTA;
    if (KEY_PRESS('H')) Pos().x += speed * DELTA;
}

