#pragma once

class Node
{
    // 길찾기(A*)에서 사용하기 위해 만든 기본 지역(혹은 좌표) 정보 클래스
    
public:
    // ...그러므로 길찾기 알고리즘과 연관성 짓기
    friend class AStar; // 나중에 A* 클래스를 만들 때 이런 이름으로 만들 것

    struct Edge //경로. 데익스트라 때와 비슷하다 (결국 A*는 D 알고리즘의 발전형)
    {
        int index;
        float cost;
        LineCollider* line;

        Edge(Vector2 start, Vector2 end)
        {
            line = new LineCollider(start, end);
            line->GetColor() = { 1, 1, 0, 1 }; // 노란색
        }
        ~Edge() { delete line; }
    };

    enum State // 이 노드 자체가 갖는 경로상의 성질
    {
        //실제 계산에서 쓰든 안 쓰든, 이론상 언급되는 노드의 성질들
        NONE, // "해당 없음" = 데이터 아님 = 안 쓸거임
        OPEN, // "갈 수 있는 곳" = 탐색 대상
        CLOSED, // "닫힌 곳" = 원래 Open이었지만 탐색이 종료되어 경우의 수에서 배제된 곳
        USING, // "탐색 중인 곳" = 조건부 탐색 대상
        OBSTACLE, // "장애물" = 데이터의 일부지만, 경로는 아닌 곳 = 탐색 대상 아님
    };

    Node(Vector2 pos, int index); //위치와 더불어 노드들 사이의 인덱스까지 미리
    ~Node();

    void Render();

    void AddEdge(Node* node);

    float GetCost() { return f; }
    void SetState(State state) { this->state = state; }

private:

    Vector2 pos;

    int index = 0;
    int via = -1;

    //경로의 비용 (종류가 셋)
    float f = 0;
    float g = 0;
    float h = 0;

    State state = NONE; //노드의 속성. 기본값은 "일단 배경 아님"

    vector<Edge*> edges; //인접경로

    Collider* collider; // 길찾기 전/후에 별도로 쓰기 위한 충돌체
};

