#include "Framework.h"
#include "DijkstraScene.h"

// 과제 : 복습 응용 or 예습 필기

// 복습 응용 : 이 씬에 나오는 탱크를 비행기 혹은 닌자로 바꿔주세요.
//            (데익스트라 클래스 읽기 복습, 각 오브젝트 클래스 수정 작성)

// 예습 필기 : 이 데익스트라 알고리즘을 바둑판에 적용하려면 어떻게 해야 할까요?
//            * 바둑판 한쪽 끝에서 다른 쪽 끝으로 가는 최단 경로를 이런 비용 비교 방식으로 내려면 어떻게 해야 할까요?
//            ....를 필기로 작성해서 카페에 올려주세요.


DijkstraScene::DijkstraScene()
{
    Init();
}

DijkstraScene::~DijkstraScene()
{
    delete tank;
    delete dijkstra;
}

void DijkstraScene::Update()
{
    if (KEY_DOWN(VK_SPACE))
    {
        //시작 지점은 탱크에서 제일 가까운 곳으로 설정
        int start = dijkstra->FindCloseNode(tank->Pos());

        //목적지는 스페이스 누를 때 마우스 커서에서 제일 가까운 곳으로
        int end = dijkstra->FindCloseNode(mousePos);

        //시작지에서 목적지로 가능 경로를 설정해서 탱크에 반영 (웨이포인트 지정)
        // -> 비슷하게 웨이포인트가 있(었)다면 비행기나 닌자도 길찾기에 활용 가능
        tank->SetPath(dijkstra->GetPath(start, end));
    }

    dijkstra->Update(); // 계산 업데이트
    tank->Update(); //탱크 정보 업데이트
}

void DijkstraScene::Render()
{
    dijkstra->Render();
    tank->Render();
}

void DijkstraScene::Init()
{
    dijkstra = new Dijkstra();
    tank = new Tank();

    // 위치 재지정이 필요하면 작성
}

void DijkstraScene::PostRender()
{
    // ImGui가 필요하면 작성
}