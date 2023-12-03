#include "Framework.h"
#include "TankScene.h"

TankScene::TankScene()
{
    gameTileMap = new GameTileMap("TextData/Test.map"); // 타일 씬에서 만든 결과 맵 쓰기
    aStar = new AStar(gameTileMap); // 타일 정보를 주고 이에 맞는 길 찾기 알고리즘 만들기

    tank = new Tank();
}

TankScene::~TankScene()
{
    delete tank;
    delete gameTileMap;
    delete aStar;
}

void TankScene::Update()
{
    //길찾기 입력
    if (KEY_DOWN(VK_LBUTTON))
    {
        int start = aStar->FindCloseNode(tank->Pos()); // 현재 탱크에서 제일 가까운 곳을 좌표로 지정
        int end = aStar->FindCloseNode(mousePos); // 현재 마우스 커서에서 제일 가까운 곳을 목적지로 지정

        aStar->GetPath(start, end, tank->GetPath()); // 시작점과 목적지로 가는 최단경로를 만들어서 탱크의 웨이포인트에 입력하기
    }

    aStar->Update(); // 필요는 없는 것 같지만 일단 호출만 (나중에 A*에서 코드가 추가될 날을 대비)
    tank->Update();
}

void TankScene::Render()
{
    gameTileMap->Render();
    aStar->Render();
    tank->Render();
}

//옵션 함수 4종
void TankScene::Init() {}
void TankScene::Quit() {}
void TankScene::PreRender() {}
void TankScene::PostRender() { tank->RenderUI(); } //ImGUI에 탱크 출력