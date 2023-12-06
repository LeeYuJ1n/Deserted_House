#include "Framework.h"

Heap::Heap()
{

}
Heap::~Heap()
{
    // Node의 포인터 인스턴스가 있지만, 여기서 만들 것이 아니라
    // 다른 곳에서 만든 것을 여기에 '힙'으로 담는 것이 목적
    // -> delete를 여기서 수행하는 것은 큰 의미 없다 (경우에 따라서는 위험할 가능성도)
}



void Heap::Insert(Node* node)
{
    heap.push_back(node);
    UpdateUpper(heap.size() - 1); //힙의 마지막을 기준으로 상부 업데이트 다시 하기
}

Node* Heap::DeleteRoot()
{
    Node* root = heap.front(); //앞의 구성요소
    
    //벡터에서 원하는 순번을 맨 뒤로 보내고 해당 순번을 pop-back으로 지우기 (지금은 0)
    Swap(0, heap.size() - 1); //순번 맨 처음과 맨 끝 교체
    heap.pop_back(); //맨 뒤 빼기

    UpdateLower(0); //새로운 힙의 0번부터 업데이트 다시 하기

    return root; // 맨 처음에 빼두었던 "앞의 구성요소"를 컴퓨터에 반환
}

void Heap::UpdateUpper(int index)
{
    int curIndex = index;
    int parent = (curIndex - 1) / 2; //현재 받은 인덱스 직전의 절반을 "부모"로 지칭

    while (curIndex != 0) // 지정 인덱스가 0이 될 때까지(순번이 처음으로 갈 때까지)
    {
        if (heap[parent]->GetCost() <= heap[curIndex]->GetCost()) // 부모(원래 나온 계산) 이동 비용이 새로 추가된 구성요소의 이동 비용보다 적으면
            return; //더 계산할 필요 없음
        
        // 그런데 여기로 왔다는 말은, 새로 추가된 노드의 Cost가 기존에 기록된 노드보다 더 적다
        Swap(curIndex, parent); // 인덱스를 기존 노드와 순번 바꾸기
        curIndex = parent; // 인덱스의 값을 부모로 (한 단계 진행)

        // 위 연산에서, 스왑이 진행됐으면 인덱스 값은 더 "상위"로 가는 거고
        // 안 됐으면 인덱스 값은 "한 칸 앞으로" 가는 거고....

        //새로운 패런트 값 구하기
        parent = (curIndex - 1) / 2;
    }
}

void Heap::UpdateLower(int index)
{
    // 하위 업데이트 : 상위와 방향이 반대라고 생각하면 편하다

    int curIndex = index; // (연산을 할) 지정 인덱스
    int lChild = (index * 2) + 1; //자식 1번 = 내 인덱스의 2배+1로 숫자 부여
    int rChild = lChild + 1; //2번 자식은 1번 자식 바로 다음으로
    int minNode = curIndex;

    while (true)
    {
        //자식의 순번이 힙에 있고, 자식의 경로상 비용이 비교 중인 지정 인덱스보다 작다면
        if (lChild < heap.size() && heap[lChild]->GetCost() < heap[minNode]->GetCost())
        {
            minNode = lChild; // 최소비용 인덱스를 지정 인덱스(curIndex)에서 자식으로 갱신
        }

        //같은 비교를 오른쪽 자식에게도 한다
        if (rChild < heap.size() && heap[rChild]->GetCost() < heap[minNode]->GetCost())
        {
            minNode = rChild; // 최소비용 인덱스를 지정 인덱스(curIndex)에서 자식으로 갱신
        }

        //만약에 두 비교연산을 했는데 최소노드가 여전히 지정 인덱스라면 (지정 인덱스가 이미 최소라면)
        if (minNode == curIndex) // 이 시점의 지정 인덱스 = 최소비용
            //break; //반복문 깨기
            return;  //아예 함수 종료

        //도출된 최소비용 노드와 지정 인덱스를 교체
        Swap(curIndex, minNode);
        curIndex = minNode; //새로운 최소 노드를 다음 지정 인덱스로 지정
        lChild = (curIndex * 2) + 1;
        rChild = lChild + 1;
    }
}

void Heap::Swap(int n1, int n2)
{
    //벡터의 swap 바로 사용
    swap(heap[n1], heap[n2]);
}
