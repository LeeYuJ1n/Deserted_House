#pragma once

class Heap
{
    // A* 알고리즘에서 노드의 정보들을 담아서 활용하기 위한 사용자 개발 자료구조 클래스
    // 이름의 Heap은 메모리 구조의 그 Heap에서 따온 것 (실제 힙과 비슷한 작동, 그렇다고 이 클래스가 진짜 힙을 대체할 건 아니다)

public:
    Heap();
    ~Heap();

    //힙이 힙으로서 작동하기 위한 함수
    void Insert(Node* node); //메모리 추가(삽입)
    Node* DeleteRoot(); //자료를 지운 후 결과를 받거나, 복사본 유지하기

    void UpdateUpper(int index); // 기준에 의한 자료의 상위구조 업데이트 (어떤 연산에 의한 변화가 생기면 영향을 받을 나머지 부분에 모두 반영)
    void UpdateLower(int index); // 기준에 의한 자료의 하위구조 업데이트

    void Swap(int n1, int n2); // 인덱스로 표현된 두 자료의 위치 바꾸기

    //다 지우기 2종
    void Clear() { heap.clear(); } // 실제로 다 지우기
    bool Empty() { return heap.empty(); } //다 지워져 있는지 확인

private:
    vector<Node*> heap; // 힙인 척하는 벡터 (내부 변수 모음)

};

