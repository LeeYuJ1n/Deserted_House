#pragma once

// "짝 맞추기 장면"

// 1. 카드를 행렬로 배치
// 2. 카드를 짝으로 클릭합니다. (하나 클릭 시에는 선택만, 둘 클릭해야 연산 시작)

// 3. 똑같은 카드가 짝이 되면 지워지게 하려고 합니다.
// 4. 단, 짝이 되는 카드가 행렬의 가장 바깥에 있어야 합니다.
// 5. 그리고 짝이 되는 카드가 행렬의 같은 "변"을 공유해야 합니다.
// 6. 그리고 짝이 되는 카드의 사이에 장애물이 있으면 안 됩니다.

class MatchingScene : public Scene
{
public:
    MatchingScene();
    ~MatchingScene();

    virtual void Update() override;
    virtual void Render() override;

private:

    //카드 짝 맞추기이므로, 카드들이 필요하다
    vector<Card*> cards;
    vector<wstring> cardTextures; // 카드에 쓸 각각의 텍스처
    
    //카드로 만든 행렬 (2중 배열)
    vector<vector<Card*>> cardBoard;

    //배열의 가로 세로
    UINT width;
    UINT height;

    // 카드를 클릭했을 때 포인터를 받을 변수
    Card* firstSelectedCard = nullptr;
    Card* secondSelectedCard = nullptr;

    //카드를 클릭했는데 짝이 틀렸을 경우에 지우기 위해 거쳐갈 변수
    float deleteTime = 0.0f;
    bool isDeleteDelay = false; // 딜레이가 발동되었가 (혹은 딜레이 규칙 설정에 쓸 수도...)

    // 위 변수를 이용해서 진행할 수 있는 함수들

    //카드 최초 세팅(생성)
    void CreateCards();
    void LoadTextures();
    void ShuffleCard(); //뒤섞기
    void SwapCard(int card1, int card2); //상호교체

    //카드를 비교했을 때... 판별용 함수
    bool IsSameCard(); // 같은 카드인가? = 같은 종류거나, 그냥 쌩 같은 카드를 두 번 클릭했거나
    bool IsOnSameLine(POINT coord1, POINT corrd2); // 두 카드의 좌표가 가장 밖인가?
    bool IsOnSameLineIncludeSelf(POINT coord1, POINT coord2); // 가장 밖이면서 한쪽이 돌출이 되어 있는가?
    bool IsUTurn(POINT coord1, POINT corrd2); // U자 짝 맞추기가 되는가 = 확실하게 같은 변을 공유하는가?

    // 비교 그 자체를 하기 위한 호출용 함수
    void CheckMatchCard();

    // 비교를 했고, 짝이 맞아서, 짝을 지우기 위한 함수
    void DeleteMatchCard(); // 짝 지우기

    //카드 선택하기
    void SelectCard(void* card);


    //방향 찾기
    // -> 카드 주변에 무엇이 있는가?

    struct EmptyDir
    {
        bool up = true;
        bool down = true;
        bool left = true;
        bool right = true;
    };
    EmptyDir GetEmptyDir(POINT coord); // 호출시 지정된 좌표의 주변 빈자리 탐색

    // QoL 편의용 함수 (Quality of Life) : 필요는 없는데 있으면 좋은 것

    UINT SHUFFLE = 1000;     //뒤섞기 수
    float cardScale = 0.5f;  //카드 크기
    UINT PAIR = 4;           //페어의 수 (사실은 잘못된 변수 설정)

    UINT REAL_PAIR = 2; //<- 이걸 2를 곱해가면서 썼어야 맞았다
    
    UINT baseAmount = 15;    //기본 카드 생성량 (페어의 영향을 같이 받는다)

    float timeToResetCard = 5.0f;
};

