#pragma once

class AStar
{
public:
    //씬에 나올 개체 필수 4종
    AStar(class GameTileMap* map); // 타일 배치를 받을 것이다 + 이런 클래스가 있을 것이다를 같이 선언

    ~AStar();
    void Update();
    void Render();

    //길찾기 함수
    void GetPath(IN int start, IN int end, OUT vector<Vector2>& path);  //실제 길 찾기
    // IN, OUT : 실제로는 의미가 없는 그냥 폼. 그러나 C++, winAPI에 (심지어 다른 일부 언어에도) 이미 정의된 용어
    // 이 매개변수가 어떤 역할을 할 것인지를 다른 개발자(및 미래의 나)에게 알려주기 위한 표기
    // IN : 이 함수 내에서 매개변수가 쓰인다(필요하다)는 의미
    // OUT : 이 함수에 어떤 결과가 (혹은 중간 결과가) 생기면 이 매개변수에 넣겠다는 의미
    // 
    // * winAPI에서 사각형 충돌이 일어났을 때 방향 정보를 위한 오버랩 벡터2를 매개변수로 받아서 저장했던 것과 같다

    int FindCloseNode(Vector2 pos); // 외부에서 '클릭에 대해 적절한 좌표'를 찾아내기 위한 함수

private:

    vector<Node*> nodes; // 좌표 정보 모음
    Heap* heap;          // 자료구조 ('자칭 힙')

    //길찾기 추가 함수
    void SetEdge(UINT width); // 경로 정보 입력. 매개변수는 필수x, 타일 지형과 같이 쓰기 위한 용도

    int GetMinNode(); // 가장 비용이 적었던 노드 찾아내기
    void Extend(int center, int end); // 연산 확장, 매개변수는 기준점(중심)과 목적지

    void Reset(); // 리셋 (계산 전에 초기 상태 복구하기)

    // 추가 함수 : 필수는 아닌데, 타일처럼 규칙적인 지형 정보가 있을 때 대단히 유용한 기능
    // 맨해튼 거리 측정 : 기하학적 거리가 아니라, x, y의 좌표 수에 의해 나오는 "이동 거리"를 뜻한다
    // 다른 이름으로는 "번지 거리" "택시 거리"라고도 한다. 특징으로는 우회로가 없으면 중간경로 모양에 상관없이 최단거리가 똑같다
    float GetManhattanDistance(int start, int end);
    float GetDiagonalManhattanDistance(int start, int end);
};

