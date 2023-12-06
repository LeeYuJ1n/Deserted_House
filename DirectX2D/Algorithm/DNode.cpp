#include "Framework.h"

DNode::DNode(Vector2 pos)
{
    // 자기 위치 매개변수에서 받아서 설정하기
    this->pos = pos;

    //콜라이더 생성 (*알고리즘보다는 길찾기 이후/이전에 좀 더 필요한 부분)
    collider = new CircleCollider(30); //반지름 30짜리 원 그리기
    collider->Pos() = pos;
    collider->UpdateWorld(); // 만들고, 콜라이더도 만들고, 1회 업데이트 (생성위치 반영만 해주기)
}

DNode::~DNode()
{
    delete collider;

    for (Edge* edge : edges)
        delete edge;
}

void DNode::Render()
{
    collider->Render();

    for (Edge* edge : edges)
        edge->line->Render();

    //collider->Render();
}

void DNode::AddEdge(DNode* node)
{
    //노드에 이어지는 다른 노드가 있을 경우, 해당 경로 정보를 추가
    Edge* edge = new Edge(node->pos, pos); //타 노드와 내 위치가 각각 들어가게
    edge->node = node; // "이어지는 노드"에 매개변수로 받은 곳을 넣기
    
    //아래 코드은 필수, 연산 방법은 옵션
    edge->cost = Distance(node->pos, pos);
    // D 알고리즘에서는 경로가 있으면 그 경로에는 비용이 필수로 들어가야 한다
    // 단, 여기서는 해당 비용을 "두 노드 사이의 거리"로 가정한다
    // (다른 비용 측정 방법이 있다면, 해당 연산으로 교체)

    // 타 노드와 이어지는 경로 설정, 비용 책정이 끝나면 벡터에 넣기
    edges.push_back(edge);
}