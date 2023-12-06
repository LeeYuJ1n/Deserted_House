#include "Framework.h"

AStar::AStar(GameTileMap* map)
{
    map->GetNodes(nodes); //맵에서 노드 정보 받아오기
    SetEdge(map->GetWidth()); //맵이 정해져 있으므로 해당 맵에 의한 경로 정보도 미리 다 받아오기

    heap = new Heap();
}

AStar::~AStar()
{
    for (Node* node : nodes)
        delete node;
    delete heap;
}

void AStar::Update()
{

}

void AStar::Render()
{
    for (Node* node : nodes)
        node->Render();
}

void AStar::GetPath(IN int start, IN int end, OUT vector<Vector2>& path)
{
    //경로 정보 초기화가 더 중요한 경우에는 함수 강제종료 전에 초기화부터 할 수도 있다
    //Reset();
    //path.clear();
    
    //경로 탐색이 불가능한 경우부터 빼내기
    if (start == -1 || end == -1) return;

    //전체 초기화
    Reset();
    path.clear();

    // 시작 정보 설정
    float _g = 0;
    float _h = GetDiagonalManhattanDistance(start, end);

    nodes[start]->f = _g + _h;
    nodes[start]->g = _g;
    nodes[start]->h = _h;
    nodes[start]->via = start;
    nodes[start]->state = Node::OPEN; // 현재 : 초기화 시 NONE이니까

    heap->Insert(nodes[start]); // 자료에 첫 노드 넣기

    while (nodes[end]->state != Node::CLOSED) // 목적의 경로가 모두 검색이 끝나서 노드가 닫히기 전까지
    {
        // 가능한 경우를 (정해진 범위에서) 모두 다 돌린다

        if (heap->Empty()) //자료가 다 비었으면
            //break; //반복문은 깨고 추가 연산은 진행
            return;  //아예 모든 연산을 종료 (자료구조가 비었으면 더 할 것도 없어서)

        // 자료가 아직 남아 있다면....

        // 노드 중에서 현재 제일 경로 비용이 낮은 노드 찾기
        int curIndex = GetMinNode();

        // 찾아낸 최소비용 노드와 주변 경로까지 탐색을 하면서 해당 정보를 반영하기
        Extend(curIndex, end); // 찾은 최소비용 노드를 중심으로 연산 확장, 이 과정에서 경로 정보 갱신까지
        //위 함수 호출이 끝나면 경우의 수 탐색이 끝난 것 = 이 노드에서는 다시 계산 안 해도 됨
        nodes[curIndex]->state = Node::CLOSED; // 노드 닫기 (계산은 끝났고 여기 다시 오지 말라)
    }

    // 여기까지 왔으면 시작점에서 목적까지 가면서 최소비용 정보는 모두 입력한 것
    // 그리고 목적지에서, 각 경우의 수에 의해 입력된 최소비용 경로의 경유지를 역산(백트랙킹)

    int curIndex = end; //위의 while{} 안과는 또 다른 지역 변수

    while (curIndex != start) // 새로운 인덱스가 시작점이 될 때까지
    {
        nodes[curIndex]->state = Node::USING; // 경로로 이용 중 (현재 코드에서는 "선택되었음!"을 뜻하기도)
        path.push_back(nodes[curIndex]->pos); // 경로 벡터에 현재 좌표의 실제 위치 추가
        curIndex = nodes[curIndex]->via;      // 다음 경유지로 지정 인덱스 재할당
    }

    //여기까지 오면 시작점부터 목적지까지 가는 모든 경로 정보가 path 벡터에 저장 완료
    path.push_back(nodes[start]->pos); // 마지막으로 시작점의 위치 넣기
}

// "입력이나 호출에 따라 가장 적절한 좌표(=바로 주변 좌표)" 반환
int AStar::FindCloseNode(Vector2 pos)
{
    // 최초 지정 거리 : 무한대
    float minDist = FLT_MAX;
    int result = -1; // 결과 없음

    for (UINT i = 0; i < nodes.size(); ++i)
    {
        float distance = Distance(pos, nodes[i]->pos);
        if (distance < minDist) // 가까운 정도가 갱신된다면
        {
            //결과 반영
            minDist = distance;
            result = i;
        }
    }

    //결과 반환
    return result;
}

void AStar::SetEdge(UINT width)
{
    //모든 노드에 대해서 반복문 돌리기
    for (UINT i = 0; i < nodes.size(); ++i)
    {
        // 자기 주변 옆, 아래, 아래의 양 옆 좌표 정보를 경로로 잇기
        // 이대로 반복문이 진행되면 모든 좌표가 8방향으로 연결되도록 할 수 있다
        if (i % width != width - 1)
        {
            nodes[i]->AddEdge(nodes[i + 1]);
            nodes[i + 1]->AddEdge(nodes[i]);
        }

        if (i < nodes.size() - width)
        {
            nodes[i]->AddEdge(nodes[i + width]);
            nodes[i + width]->AddEdge(nodes[i]);
        }

        if (i < nodes.size() - width && i % width != width - 1)
        {
            nodes[i]->AddEdge(nodes[i + width + 1]);
            nodes[i + width + 1]->AddEdge(nodes[i]);
        }

        if (i < nodes.size() - width && i % width != 0)
        {
            nodes[i]->AddEdge(nodes[i + width - 1]);
            nodes[i + width - 1]->AddEdge(nodes[i]);
        }
    }
}

int AStar::GetMinNode()
{
    // 경로가 제일 적은 좌표 구하기

    // 원칙적으로 하는 계산
    // 1. 모든 노드를 순차적으로 돌립니다
    // 2. 그 노드에서 자기 주변 경로로 가기 위한 최소 비용을 도출합니다
    // 3. 최소값을 계속 갱신한 후(for 반복문), 최종 결과를 반환받습니다.
    // (따로 자료구조가 필요없는 데익스트라 알고리즘이었다면 여기서 코드를 다 적어야 했을 것)

    // 위 계산에서 "특정한 위치를 새로 준 다음, 기존 결과들과 비교한다"라는 구절을 추가하면?
    // "해당 위치가 기존 결과에서 어느 정도의 비용 수준을 가지는지 갱신한다" 는 것과 비슷한 이야기

    // = '힙' 클래스의 이진 트리에서 가장 위에 있는 노드가 현재 갱신된 최소 비용 노드다!

    // 이진 트리의 최상부 노드를 떼어내고, 해당 노드를 받은 다음 그 노드의 인덱스를 컴퓨터에게 또 준다
    return heap->DeleteRoot()->index;

    // * 클래스가 잘 나뉘면 쓰는 쪽에서는 만들어진 기능을 호출만 잘 해도 된다
}

//...그리고 위 함수에서 최소 경로를 잘 구하려면 이 안에서도 경로 값을 넣어줄 때 잘 넣어줘야 한다

void AStar::Extend(int center, int end)
{
    for (Node::Edge* edge : nodes[center]->edges) //매개변수로 받은 경유지의 경로 정보 돌리기
    {
        int index = edge->index;

        //못 가는 곳 제외
        if (nodes[index]->state == Node::CLOSED) continue; // 검색 끝났거나 어떤 이유로든 제외됐으면 제외
        if (nodes[index]->state == Node::OBSTACLE) continue; //길이 아니어도 제외

        float _g = nodes[center]->g + edge->cost; //좌표가 가졌던 'g'와 경로의 비용을 합친 것
        float _h = GetDiagonalManhattanDistance(index, end); // 지정 좌표에서 목적지까지의 "지도상 거리" : 판단의 기준점이 된다
        // 지금은 대각선을 포함한 택시 거리를 계산에 넣고 있지만, 여기에 그냥 택시 거리를 쓸 경우, 좀 더 딱딱한 비교를 진행할 수 있다
        // _g는 실제 경로의 비용을 책정하지만, 데이터의 영향을 너무 크게 받는다
        // _h는 실제 경로의 비용이 아니지만, 순수 거리를 책정해주면서 _g가 너무 우회하는 결과를 내지 않게 하는 판단 기준이 된다

        float _f = _g + _h; // 이 둘을 합치면 비교를 위한 최종 결과를 받아낼 수 있다

        //여기서 우리는 노드의 경로 비용 변수 f, g, h의 이름을 유추해볼 수 있다 (*사실은 역두문자지만...)
        // f : Final, 최종 결과
        // g : Geometric, 지형 내의 정보값 (경로 비용)
        // h : Heuristic, "휴리스틱" 정보값 (연산의 추정화, 실제 정보에 가중치를 더해서 판단 기준을 생성)

        // 지금 찾아낸 f 값을 활용

        //일단은 노드가 "갈 수 있는 길"이라고 칠 때
        if (nodes[index]->state == Node::OPEN)
        {
            // 비용 정보 갱신
            if (_f < nodes[index]->f)
            {
                nodes[index]->g = _g;
                nodes[index]->f = _f;
                // nodes[index]->h = _h; // <- 어차피 타일이 움직일 거 아니니까 1회 계산만으로도 충분. 필요하면 나중에 또 계산하면 그만
                nodes[index]->via = center; // 노드의 경유지가 현재의 경유지가 되도록
            }
        }
        //(옵션) 데이터에 원래 없었지만 새로 필드에 추가되는 영역이 있다면 (있다고 가정하고 작성)
        else if (nodes[index]->state == Node::NONE)
        {
            //노드에 경로 정보 다 집어넣기
            nodes[index]->g = _g;
            nodes[index]->h = _h; // 새로 경로 정보 채워넣기
            nodes[index]->f = _f;
            nodes[index]->via = center;
            nodes[index]->state = Node::OPEN; // 갈 수 있는 길로 표시

            heap->Insert(nodes[index]); // 노드 누적에 새로운 노드 넣기
        }
    }
}

void AStar::Reset()
{
    // 계산의 처음 혹은 끝에 진행할 노드 정보 전체 초기화

    for (Node* node : nodes)
    {
        if (node->state != Node::OBSTACLE)
            //node->state = Node::OPEN; //길 "갈 수 있음"으로 설정하기
            node->state = Node::NONE; // 위 Extend 함수와 (현재 작성 버전) 같이 쓸 경우, 결과적으로 더 백지에 가까운 정보를 설정 가능
    }

    //노드가 Open인 경우, 각 노드의 정보를 일괄/선택해서 heap에 주면 된다

    //현재 작성 버전의 경우, 그냥 heap을 지우면 된다 (추가는 extend에서 다 해주니까)
    heap->Clear();

    //이렇게 NONE 상태도 잘 사용하면 빠른 연산에 도움이 된다 (+지도의 확장성에도 도움이 된다)
    // -> 대신 각 노드에 대한 부분 통제는 힘들 수도 있다 (부분 통제가 필요할 때는 결국 Open 노드를 직접 개발자가 수정해야)
}

// 각 경로의 비용 구하기 (경로의 비용은 원래는 알고리즘에서 정하기 나름이지만,
// 여기서는 기하학적 거리가 곧 비용이라고 가정한다)

float AStar::GetManhattanDistance(int start, int end)
{
    // 택시 거리 : X간의 거리와 Y간의 거리를 단순히 합하기만 하면 된다 (기본)

    Vector2 startPos = nodes[start]->pos; //(순번으로 지정된) 시작 좌표의 실제 위치
    Vector2 endPos = nodes[end]->pos;     // 목적지의 위치

    Vector2 distance = endPos - startPos; //벡터로서의 차

    // 함수의 결과 : x 간의 거리와 y 간의 거리를 그대로 합치기
    return abs(distance.x) + abs(distance.y);
}

float AStar::GetDiagonalManhattanDistance(int start, int end)
{
    // "대각선" 택시 거리 구하기 : 일단은 대각선이 포함되고, x, y 좌표값도 계산에 넣는 거리 계산법
    // 구체적으로는 다음과 같다
    // 1. 시작점과 목적지 사이에 정사각형 모양이 있다고 치고, 해당 정사각형의 대각선 길이를 계산한다
    // 2. 정사각형에 포함되지 않는 남은 직사각형 구역의 "순수 택시 거리"를 계산한다
    // 3. 1과 2를 합친다

    Vector2 startPos = nodes[start]->pos; //(순번으로 지정된) 시작 좌표의 실제 위치
    Vector2 endPos = nodes[end]->pos;     // 목적지의 위치

    Vector2 distance = endPos - startPos; //벡터로서의 차

    //결과 벡터의 성분을 절대값으로
    float x = abs(distance.x);
    float y = abs(distance.y);

    //최대 최소 구하기
    float maxDist = max(x, y);
    float minDist = min(x, y);

    //차이 거리와 정사각형의 대각선 길이를 합쳐서 최종 결과를 구하는 것
    return (maxDist - minDist) + sqrt(minDist * minDist * 2);

    // * 체스나 장기 좋아하시는 분은 나이트, 마, 상의 행마를 떠올려보세요. 그게 대각선 택시 거리의 기하학적 형태입니다.
}