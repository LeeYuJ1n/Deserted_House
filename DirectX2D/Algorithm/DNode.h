#pragma once

class DNode
{
    friend class Dijkstra; // 싱글턴처럼 순서 상관없이 데익스트라 클래스와 연관성을 주고받으므로 미리 선언

    struct Edge // Edge : D 알고리즘에서 각 D 노드와 연관된 노드의 여부, 그 사이에서 생긴 연관성 정보를 뜻한다
                // (D 알고리즘에서 이동은 결국 점에서 점이 아니라 "지역에서 지역"이라는 의미를 포함하고 있다)
    {
        DNode* node; // 이곳과 이어지는 (다른) 노드의 포인터
        float cost; // <- Movement Cost, 이동에 드는 비용

        LineCollider* line; // *이 실습에서 정보로 추가하는 라인 콜라이더

        //구조체의 생성자 (구조체도 생성자가 있다)
        Edge(Vector2 start, Vector2 end)
        {
            line = new LineCollider(start, end);
        }
        ~Edge()
        {
            delete line;
        }
    };

    //D-노드 : 데익스트라 알고리즘에서 위치 정보를 담당하는 클래스
    //         (위치 : 시작점, 목적지, 경유지 중 하나)

    // (기본 원칙)
    // 각 노드는 다른 노드와 연관을 맺거나, 맺지 않을 수 있다
    // 한 노드에서는 연관을 맺은 다른 노드로만 갈 수 있다

public:

    //이 클래스의 생성자, 소멸자
    DNode(Vector2 pos);
    ~DNode();

    //렌더
    void Render();

    //노드는 업데이트의 대상은 아닐 것 : 프레임마다 움직일 필요는 없으므로
    // -> 혹시 그런 노드가 생긴다면 void Update() 추가할 필요가 생길 것

    //대신 Update보다 노드에 시급한 것 : 다른 노드와의 연관성을 (다른 곳에서) 추가하기
    void AddEdge(DNode* node);

private:
    
    Vector2 pos; // 트랜스폼 대신 위치 정보 직접 갖기 (움직이지 않을 물건이 트랜스폼이 있어봤자 안 쓸 거라서)

    bool isClosed = false; // 이 노드가 외부에서 접근 가능한가 ("닫혔는가?") 여부

    int index = 0; //노드들 사이에서 "이" 노드가 가질 인덱스
    int via = -1;  //경유 여부, 혹은 경유지 정보, 혹은 경유 비용 등 경유 상황에서 쓰일 변수
                   // "via" : ~~를 통해서 (Ban via PickC : 캐릭터 선택 중의 배제 = 픽밴, 사람 밴이 아님)

    float cost = FLT_MAX ; //기본 이동 비용, 기본값은 "컴퓨터가 감당 가능한 최대치" (= 여기론 이동 불가능)
                           //이후 연산 중에 실질 비용을 재계산

    vector<Edge*> edges; // 이 노드와 현재 연결된 노드들

    Collider* collider; // * 길찾기와 별도로 길찾기 후 이동 연산에 (주로) 사용할 콜라이더
};

