#pragma once

class Dijkstra
{
    // 데익스트라 알고리즘 담당 클래스 : 각 경로별 비용 비교 후 최저비용 경로를 선택

public:
    //기본 4종 세트
    Dijkstra();
    ~Dijkstra();

    void Update();
    void Render();

    //데익스트라 알고리즘의 실제 사용 기능들
    int FindCloseNode(Vector2 pos); // "지정받은 지점에서 가까이 있는 노드들 검색" : 주변에 뭐가 있는가?
    int FindMinCostNode();          // 최소비용 경로 검색
    void SetEdgeInfo(int index); //경로정보 세팅
    
    void ResetNodes(); // 노드 (수행) 리셋

    vector<Vector2> GetPath(int start, int end); //경로(경우의 수) 보존용 (장기보존 필요가 없어서 함수로만)

    // 씬에서 노드 추가가 필요한 경우, 추가 함수 작성 후 CreateNode 함수를 토스하듯이 재호출
    void CallCreateNode(Vector2 pos) { CreateNode(pos); }

private:

    //노드 정보 (재)생성
    void CreateNode(Vector2 pos);

    vector<DNode*> nodes; // 위치들의 정보는 계속 갖고 있어야 하므로 변수로 작성

    DNode* selectNode = nullptr; // 현재 선택 중인 노드

};

