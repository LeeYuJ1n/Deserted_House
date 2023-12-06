#include "Framework.h"

Node::Node(Vector2 pos, int index)
    : pos(pos), index(index)
{
    //this->pos = pos;
    //this->index = index;

    collider = new CircleCollider(15); // 반지름 15의 원 그려서 표시
    collider->Pos() = pos;
    collider->UpdateWorld();
}

Node::~Node()
{
    for (Edge* edge : edges)
        delete edge;

    delete collider;
}

void Node::Render()
{
    //collider->Render(); //어찌 됐든 원 표시 (기본, 필수)

    //State의 경우의 수에 따라 콜라이더 색 표시를 다르게 하면서 렌더

    switch (state) // if를 해도 되지만, enum의 특성상 중복 없음, 애매한 경우 없음. switch와 잘 어울린다
    {
    case Node::NONE:
        collider->GetColor() = { 0, 1, 1, 1 }; // 청록색
        break;

    case Node::OPEN:
        collider->GetColor() = { 0, 0, 1, 1 }; // 파란색
        break;

    case Node::CLOSED:
        collider->GetColor() = { 0, 0, 0, 1 }; // 까만색
        break;

    case Node::USING:
        collider->GetColor() = { 0, 1, 0, 1 }; // 초록색
        break;

    case Node::OBSTACLE:
        collider->GetColor() = { 1, 0, 0, 1 }; // 빨간색
        break;
    }

    //색을 준 다음에 다시 렌더
    collider->Render();
}

void Node::AddEdge(Node* node)
{
    Edge* edge = new Edge(node->pos, pos); // 목표와 여기의 위치가 시작, 끝으로 들어가게
    edge->index = node->index; //경로 인덱스에 목표 정보 반영
    edge->cost = Distance(node->pos, pos); // *이번에도 (실습 중이니까) 경로상의 비용은 거리와 동일하다는 가정으로 진행

    edges.push_back(edge);
}