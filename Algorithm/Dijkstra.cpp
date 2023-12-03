#include "Framework.h"

Dijkstra::Dijkstra()
{
    // 노드를 여기서 만든다면 여기서 생성자를 작성을 할 텐데
    // -> 노드가 앱 내에서 만들어지면? 혹은 씬에서 만들면?
    // -> 여기서 할 일이 없다 : 생성자 코드는 현재 보류
}

Dijkstra::~Dijkstra()
{
    for (DNode* node : nodes)
        delete node;
    //'선택 중인 노드'는 어차피 위에서 같이 지워졌을 것
}

void Dijkstra::Update()
{
    // 앱 내에서 노드 만들기 : 입력이 들어오면 그 자리에 노드를 생성
    if (KEY_DOWN(VK_LBUTTON))
    {
        CreateNode(mousePos); // 좌클릭 시 커서 위치에 노드 생성
    }

    // 앱 내 조작 추가 : 마우스 우클릭 드래그 시 경로 설정
    if (KEY_DOWN(VK_RBUTTON))
    {
        for (DNode* node : nodes)
        {
            if (node->collider->IsPointCollision(mousePos))
            {
                selectNode = node;
                break;
            }
        }
    }

    if (KEY_UP(VK_RBUTTON))
    {
        //선택된 노드가 없으면 그대로 종료
        if (selectNode == nullptr) return;

        for (DNode* node : nodes)
        {
            // 시작지와 목적지가 같아도 종료 (단 조작미스/노드 겹침 등을 감안해서 return 대신 반복문 내의 종료로)
            if (node == selectNode) continue;

            // 여기까지 오면 조작미스/노드 중복 없이 드래그한 위치에서 연산 가능
            if (node->collider->IsPointCollision(mousePos)) //그리고 이 노드가 커서 위치와 겹치면
            {
                node->AddEdge(selectNode); // 드래그 끝난 노드에 선택했던 노드를 경로로 추가
                selectNode->AddEdge(node); // 반대도 마찬가지
                // selectNode = nullptr; // 옵션 : 선택을 완전히 해제하고 싶은 경우
                break;
            }
        }
    }

    // 길을 찾아가는 기능도 필요한데,
    // 길찾기 클래스 내에서는 "길을 누가 찾아갈 것인가?"가 빠져 있으므로 보류
    // -> 씬에서 해당 기능을 호출하게 될 수도...
}

void Dijkstra::Render()
{
    for (DNode* node : nodes)
        node->Render(); //노드 (속 콜라이더들) 렌더
}

int Dijkstra::FindCloseNode(Vector2 pos)
{
    float minDist = FLT_MAX; // 검색에 쓸 최초 기준 최소 검색 거리 : 기본값은 윈도우가 아는 최대치

    int result = -1; //결과 기본값 : "없음"의 -1

    for (int i = 0; i < nodes.size(); ++i)
    {
        float distance = Distance(pos, nodes[i]->pos);

        if (distance < minDist) // 기준보다 거리가 가까운 노드가 있으면
        {
            minDist = distance; //기준을 갱신해주고
            result = i; //결과 반영
        }

        //이 반복문이 끝나면 지정된 위치에서 가장 가까운 "주변" 노드 검색 완료
    }

    return result;
}

int Dijkstra::FindMinCostNode()
{
    //위 함수와 원리는 같고, 비교 대상만 거리가 아닌 "비용"

    float minCost = FLT_MAX;

    int result = -1;

    for (int i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i]->isClosed) continue;

        if (nodes[i]->cost < minCost)
        {
            minCost = nodes[i]->cost;
            result = i;
        }
    }

    return result;
}

void Dijkstra::SetEdgeInfo(int index)
{
    if (index == -1) return; // 인덱스가 "없으면" 바로 종료

    float cost = nodes[index]->cost; // 현재 노드의 비용을 반영해서 비용 임시 생성

    for (DNode::Edge* edge : nodes[index]->edges)
    {
        if (edge->node->cost > cost + edge->cost)
        {
            // 엣지에 등록된 비용이(현재 : 두 노드의 거리가) 각 노드의 비용(기본값 = 최대)보다 적다면

            // 해당 정보를 반영
            edge->node->cost = cost + edge->cost;
            // * 노드의 비용 기본값은 최대지만, 이 함수가 호출될 때, 시작지점 비용은 0이 되었기 때문에 0부터 비용을 점증시킬 수 있다

            edge->node->via = index; // 노드의 경유지를 매개변수로 받은 인덱스로 등록 (이 경유지가 경로 역추적 때 쓰인다)
        }

    }

    nodes[index]->isClosed = true; // 모든 계산이 끝난 후, 노드 닫기 (="나한테서 나한테로" 가는 경우 빼기)
}

void Dijkstra::ResetNodes()
{
    // 노드 정보 리셋 : 경로 검색 중에 바뀐 값을 모두 원위치로
    // -> 기본값 다시 입력
    for (DNode* node : nodes)
    {
        node->isClosed = false; // "갈 수 있음"
        node->via = -1;         // "경유지 없음"
        node->cost = FLT_MAX;   // "비용, 그냥 안 가는 게 좋음"
    }
}

vector<Vector2> Dijkstra::GetPath(int start, int end)
{
    if (start == -1 || end == -1) return vector<Vector2>(); // 시작이나 끝이 없을 경우 (= 경로 성립이 안 되면) 텅 빈 벡터 주기 (=그냥 종료)

    //이전 연산이 있었으면 정리부터 하고 진행
    ResetNodes();

    // 시작 쪽 노드 정보 초기화
    int curIndex = start;
    nodes[curIndex]->cost = 0; // 안 움직였으니 비용은 0
    nodes[curIndex]->via = start; //어디를 거칠 거냐? -> 일단 자기 자신

    for (DNode* node : nodes)
    {
        //노드의 정보 추출하기 (엣지 정보 추출)
        SetEdgeInfo(curIndex);

        // 정보 추출 후에, 갈 수 있는 노드 중에서 최소비용 경로를 가진 노드 선택
        curIndex = FindMinCostNode();
    }
    // 여기까지 오면 1차로 경로 적합 여부를 판단 가능
    // 2차로는 연산 과정에서 뺄 경우의 수가 있다면 해당 노드를 닫아서 처리 가능

    // 이 시점에서도 이론적으론 경로 설정을 시도할 수 있지만, 더 확실하게 하려면 이후의 연산 수행

    // 검산(Recal) / 역추적(Backtrack) : 뒤에서 또 한번 진행
    curIndex = end;

    vector<Vector2> path; // 최종 결과를 위한 벡터 생성

    while (curIndex != start) // 선택 인덱스가 시작이 될 때까지
    {
        path.push_back(nodes[curIndex]->pos);
        curIndex = nodes[curIndex]->via; // <- 정보 추출 과정 어딘가에서 via가 각 노드에 재설정되어야 한다는 뜻
        
        //여기로 오면 뒤에서부터 각 노드의 위치와 경유지가 차례로 벡터와 curIndex에 등록

        //비상용
        if (curIndex == -1) break;
    }

    //마지막으로 벡터에 시작 노드를 포함
    path.push_back(nodes[start]->pos);

    // * 왜 검산을 굳이 하는가? 왜 뒤에서부터 또 연산하는가?
    //   -> 계산 중에 보이는 부분 정보와 최종 합계가 사실은 다를 수도 있어서
    //      (거리가 긴 직선 1개와 짧은 직선 여러 개를 비교한다든가....)
    //      -> 검산의 목적을 염두에 둔다면 지금 코드도 1000% 충분하지 않다
    //         (현재는 어디까지나 거리가 곧 비용이기 때문에 검산해도 어차피 짧으면 빠르다 -> 2번 계산할 이유가 없다)

    //   그래서 데익스트라 알고리즘은 만능보다는 일종의 백지에 가깝고, 실제로는 수많은 변형이 존재

    return path;
}

void Dijkstra::CreateNode(Vector2 pos)
{
    DNode* node = new DNode(pos);
    node->index = nodes.size(); // 현재 벡터의 크기(=마지막 순번)을 만들어진 노드의 인덱스로 재지정

    nodes.push_back(node); //새로 만들어진 노드를 벡터에 추가
}
