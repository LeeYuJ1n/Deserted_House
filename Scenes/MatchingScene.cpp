#include "Framework.h"
#include "MatchingScene.h"


// 24일 과제 : 택1

// 예습 1가지

// -> 카드를 클릭하면 내 마우스 커서에 카드 모양이 복제되어서 따라다니게 해주세요.
//    클릭에 따른 이벤트, 마우스 위치 받기 등의 복습을 겸합니다.

// -> 타일 배치에 의한 게임 필드 개념에 대해서 검색해서 필기하고 올려주세요.

// 도전 과제 (내일 당장은 아니지만 중간에 시간 내서 한번 도전해봅시다)

// -> 텍스처 자르기 + 타일의 규칙적 배치 + 클릭과 상호작용 등을 이용해서...
//    슬라이드 퍼즐을 한번 도전해봅시다 (DX 방식으로)


//-----------------------------------------------

// 25일 예습 : 바이너리 리더와 라이터 클래스 구현

// 바이너리 리더, 라이터 : 바이너리 알고리즘의 응용 중 하나, 컴퓨터 파일을 이진 방식으로 읽는 것

// 기초적인 파일 입출력이라서 자주 쓰이진 않지만, 적소에 쓰이면 대단히 좋은 효율을 내기도 한다

// (* 리더, 라이터의 경우 우리가 알고리즘 그 자체를 만들 것이 아니다 : DX,Windows의 기능을 써서
//    실제 파일의 내용을 읽고 쓰겠다는 것)



MatchingScene::MatchingScene()
{
    //카드 텍스처를 읽은 다음
    LoadTextures();
    //카드를 생성하고 (벡터로)
    CreateCards();
    //순서를 뒤섞기
    ShuffleCard();

    // 카드 선택(void*) 함수를 실제로 만들어진 카드들에 배정
    Observer::Get()->AddParamEvent
    ("SelectCard", bind(&MatchingScene::SelectCard, this, placeholders::_1));

    // 더 필요한 게 있으면 와서 작성...
}

MatchingScene::~MatchingScene()
{
    for (Card* card : cards)
        delete card;
}

void MatchingScene::Update()
{
    if (firstSelectedCard != nullptr)
    {
        //선택된 카드가 있으면 지연 삭제 대기 상태

        deleteTime += DELTA;

        if (deleteTime > timeToResetCard)
        {
            //isDeleteDelay = true;
            DeleteMatchCard();
        }
    }

    //전체 카드 업데이트
    for (Card* card : cards)
        card->Update();
}

void MatchingScene::Render()
{


    for (Card* card : cards)
        card->Render();
}

void MatchingScene::CreateCards()
{
    // 전체 개수 (기본 생성량에 페어 수를 곱하기)
    UINT totalCardNum = baseAmount * PAIR;

    //가능한 인수 목록 제작
    vector<UINT> factors; // 인수 벡터
    for (UINT i = 1; i <= totalCardNum; ++i)
    {
        if (totalCardNum % (i) == 0)
            factors.push_back(i); //가능한 인수 목록에 i를 추가
    }

    //인수 목록의 크기 절반 잘라서 하나 더 받기 (인수의 A, B와 B, A는 같은 쌍이니까)
    UINT halfFactors = factors.size() / 2;

    //가능한 인수 목록의 전체 크기가 홀수면 딱 중간에 해당하는 인수를 쓰고,
    //짝수면 가장 중간에 가까운 벡터상 위치에 해당하는 인수를 써서,
    //이번 게임에 쓸 가로와 세로를 구하기
    if (factors.size() % 2 == 0)
    {
        width = factors[halfFactors];
        height = factors[halfFactors - 1]; //위에서 쓴 인수의 딱 앞자리로
        
        // 예 : 1 2 3 4 5 6 7 8 9 0 이라는 목록이 있으면 이 중에서
        //      1 2 3 4 [5 6] 7 8 9 0 <- 5와 6 사용
    }
    else //홀수면
    {
        width = factors[halfFactors];
        height = factors[halfFactors];

        // 예 : 1 2 3 4 5 6 7 8 9 라는 목록이 있으면 이 중에서
        //      1 2 3 4 [5] 6 7 8 9 <- 5를 사용
    }
    // 배치를 했을 때, 최대한 정사각형에 가까운 직사각형을 만들고자 하는 것이 목적
    // 위 조건문을 다른 곳에도 활용 가능

    // 크기 정하기와 텍스처 (첫 번째) 넣기까지 한 방에
    Vector2 size = Texture::Add(cardTextures[0])->GetSize() * cardScale;

    //전체 행렬의 크기
    Vector2 totalHalfSize = size * Vector2(width, height) * 0.5f;
    //행렬의 시작점
    Vector2 boardOffset = Vector2(CENTER_X, CENTER_Y) - totalHalfSize + size * 0.5f;
    // 카드 1~반개 정도 공백

    //배치

    cardBoard.resize(height); //행 = y축 만큼 리사이즈
    for (vector<Card*>& vec : cardBoard)
        vec.resize(width);

    for (UINT y = 0; y < height; ++y) //y : j 대신 쓴 것
    {
        for (UINT x = 0; x < width; ++x) //x : i 대신
        {
            Vector2 pos = boardOffset + Vector2(x, y) * size;

            UINT index = (y * width + x) / PAIR; //1부터 60까지 숫자를 배정한 후 페어 수만큼 나누기
            Card* card = new Card(cardTextures[index]); //인덱스에 해당하는 파일 이름으로 텍스처 및 카드 생성
            // -> 한 묶음당 페어 수만큼의 카드가 존재할 것

            //만들어진 카드 조정
            card->Pos() = pos;
            card->Scale() = card->Scale() * cardScale; //헤더에서 정한 크기 비율만큼 조정
            card->SetCoord(x, y); //카드가 현재 가진 좌표를 x, y로 부여

            cards.push_back(card); //만들어진 전체 카드 벡터에 추가
            cardBoard[y][x] = card; // 초기화된 카드 보드의 해당 좌표에도 이 카드를 할당
        }
    }
}

void MatchingScene::LoadTextures()
{
    // 텍스처 파일을 여러 개를 미리 읽은 다음에 각 카드를 위해 준비하는 단계

    // *윈도우의 제공 함수 두 가지 사용 (필요하면 검색; "이런 게 있구나" 이해)

    WIN32_FIND_DATA findData; // 하드에서 데이터 찾기
    HANDLE handle = FindFirstFile(L"Textures/Cards/*.png", &findData);

    // WIN32_FIND_DATA : 하드(혹은 디스크)에 있는 파일의 정보를 모아 보존하는 구조체
    // HANDLE = 정체는 void*, 다만 이런 형태로 쓰면 윈도우의 탐색기 기능 등을 수행해서
    //          해당 결과를 받아서 2차 연산으로 전달시킬 수가 있다 (그래서 "핸들")
    //          * 핸들, 핸들러 : 요구받은 조건이 발생할 경우(이벤트, 직접 수행) 조건 결과를 다음 함수에 전달하는 역할 (관리자)

    bool continued = true; // 데이터가 남은 게 있는지 체크
    wstring filename; //들어온 파일 이름

    while (continued) //데이터가 남은 부분이 있는 동안 계속 = 검색된 파일이 있으면
    {
        filename = L"Textures/Cards/"; // 경로 지정 후
        filename += findData.cFileName; //찾아낸 파일 이름을 합친다

        cardTextures.push_back(filename); // 파일 전체 경로명을 벡터에 넣기

        continued = FindNextFile(handle, &findData);
        //findData에 다음 파일 이름이 있는지 handle로 검출
        // 있으면 true 없으면 false
    }

    // 여기까지 오면 : 폴더 안의 모든 파일 이름을 검색해서 벡터에 넣었다
}

void MatchingScene::ShuffleCard()
{
    // 뒤섞기 : 빙고 때하고 대충 비슷하게
    // -> 카드가 포인터 인스턴스로 나와서, 순서 관리는 1중 벡터로, 실제 출력은 2중 벡터로 나뉜 상황
    // -> 어떤 의미에서는 차라리 쉽기도 (코드 양은 불어날 것 : 그래서 함수를 지금 둘로 분리)

    // 분리된 뒤섞기 함수 : 순서 섞기용 본 함수와, 실제로 카드를 바꾸기 위한 아래 함수

    for (int i = 0; i < SHUFFLE; ++i)
    {
        int rand1 = Random(0, cards.size()); // 전체 카드 숫자 중에서 아무 순번이나 하나 찍기
        int rand2 = Random(0, cards.size());

        if (rand1 != rand2) SwapCard(rand1, rand2); // 실제 카드 바꾸기는 분리해서 밑에 작성
    }
}

void MatchingScene::SwapCard(int card1, int card2)
{
    //출력에 쓸 위치 바꾸기
    Vector2 tempPos = cards[card1]->Pos();
    cards[card1]->Pos() = cards[card2]->Pos();
    cards[card2]->Pos() = tempPos;

    //행렬로서의 배치에 쓸 좌표도 바꾸기
    POINT tempCoord = cards[card1]->GetCoord();
    cards[card1]->SetCoord(cards[card2]->GetCoord());
    cards[card2]->SetCoord(tempCoord);

    //바뀐 좌표를 받아서 보드에도 반영하기
    POINT newCoord1 = cards[card1]->GetCoord();
    POINT newCoord2 = cards[card2]->GetCoord();

    Card* tempCard = cardBoard[newCoord1.y][newCoord1.x]; //보드 배치 내에서 포인터 인스턴스(지칭)를 교체
    cardBoard[newCoord1.y][newCoord1.x] = cardBoard[newCoord2.y][newCoord2.x];
    cardBoard[newCoord2.y][newCoord2.x] = tempCard;

    // 여기까지 오면 전체 카드 (1중 벡터) 에서 카드 순서가 바뀌고
    // 실제로 출력된 전체 판에서도 두 카드의 위치가 바뀐다
}

bool MatchingScene::IsSameCard()
{
    // 카드가 짝이 맞는지, (더불어서 완전 같은 카드를 또 선택하지는 않았는지)

    // 쌩 같은 카드를 선택한 경우
    if (firstSelectedCard == secondSelectedCard)
    {
        MessageBox(hWnd, L"같은 카드를 두 번 선택했습니다.", L"Error", MB_OK);
        return false;

        // MassageBox : WinAPI 환경에서 사용 가능한 제공 함수 중 하나
        //              메시지가 포함된 팝업 창을 띄워주는 것이 역할
        //              WinAPI 쌩 기능을 쓰기 때문에 잘 쓰이지 않는다...

        // 매개변수 : hWnd = 현재 윈도우
        //           L"같은 카드를..." = 메시지 박스 본문 내용
        //           L"Error" = 메시지 박스 타이틀, 동시에 구분
        //           MB_OK = 이 메시지 박스에서 띄울 버튼, 종료 조건.
    }

    // 짝이 맞는 경우
    if (firstSelectedCard->GetKey() == secondSelectedCard->GetKey())
        //현재는 파일 이름이고, 경우에 따라 타입ID, 경우에 따라 태그.... 등의 데이터가 있겠지만
        // 아무튼 같은 이런 Key-Data를 공유한다면 곧 같은 생성 과정을 거쳐서 만들어진 개체라고 판단 가능
        // (인스턴스를 만들 때도 같은 생성 과정, 같은 리소스를 쓸 때는 공통된 Kay-Data를 붙여주면 좋다)
    {
        return true;
    }

    //여기까지 오면 완전히 같은 카드는 아닌데, 그렇다고 짝이 맞는 것도 아닌 경우
    MessageBox(hWnd, L"짝이 맞지 않습니다.", L"Error", MB_OK);
    return false;
}

bool MatchingScene::IsOnSameLine(POINT coord1, POINT coord2)
{
    //그냥 좌표가 다른 경우
    if (coord1.x != coord2.x && coord1.y != coord2.y)
    {
        // 결과 메시지를 띄울 수도 있지만, 이 조건이 틀려도 다음 조건이 맞을 수 있으므로 메시지 생략
        return false;
    }

    // 열이 같은 경우 (같은 세로줄 = 같은 x)
    if (coord1.x == coord2.x)
    {
        //높이 범위 찾기
        int minY = min(coord1.y, coord2.y);
        int maxY = max(coord1.y, coord2.y);

        for (int y = minY + 1; y < maxY; ++y)
        {
            //중간에 장애물이 껴 있으면
            if (cardBoard[y][coord1.x]->Active()) return false; // 메시지는 마찬가지로 생략
        }
    }

    // 행이 같은 경우 (y)
    if (coord1.y == coord2.y)
    {
        //열 거리 범위 찾기
        int minX = min(coord1.x, coord2.x);
        int maxX = max(coord1.x, coord2.x);

        for (int x = minX + 1; x < maxX; ++x)
        {
            //중간에 장애물이 껴 있으면
            if (cardBoard[coord1.y][x]->Active()) return false;
        }
    }

    // 여기까지 오면 x, y 좌표 중에 하나가 일치하고 (둘 다 일치하면 실행도 안 될 거고)
    // 서로 간의 위치 중간에 장애물도 없다는 뜻
    // =같은 변 위치를 공유한다는 뜻

    return true;
}

bool MatchingScene::IsOnSameLineIncludeSelf(POINT coord1, POINT coord2)
{
    /*
    if (coord1.x != coord2.x && coord1.y != coord2.y) return false;

    if (coord1.x == coord2.x)
    {
        int minY = min(coord1.y, coord2.y);
        int maxY = max(coord1.y, coord2.y);

        for (int y = minY + 1; y < maxY; ++y)
        {
            if (cardBoard[y][coord1.x]->Active()) return false;
        }
    }

    if (coord1.y == coord2.y)
    {
        int minX = min(coord1.x, coord2.x);
        int maxX = max(coord1.x, coord2.x);

        for (int x = minX + 1; x < maxX; ++x)
        {
            if (cardBoard[coord1.y][x]->Active()) return false;
        }
    }

    return true;
    */

    return IsOnSameLine(coord1, coord2);
}

bool MatchingScene::IsUTurn(POINT coord1, POINT coord2)
{
    EmptyDir dir1 = GetEmptyDir(coord1);
    EmptyDir dir2 = GetEmptyDir(coord2);

    // 도출한 "빈 자리 방향"끼리 계산

    // 제일 간단한 경우 : 첫 카드도 해당 변의 가장자리, 두 번째 카드도 가장자리인 경우
    // = 사실상 같은 변을 공유한 상황이나 다름없는 경우

    if (dir1.right && dir2.right) return true;
    if (dir1.left && dir2.left) return true;
    if (dir1.up && dir2.up) return true;
    if (dir1.down && dir2.down) return true;

    // 여기까지 오면 각 카드가 가장자리라기엔 힘든데,
    // 꼬불꼬불하게 이어질 가능성은 있을지도 모르는 상태

    //오른쪽...
    for (int x = coord1.x + 1; x < width; ++x)
    {
        POINT tempCoord1 = { x, coord1.y };

        if (cardBoard[tempCoord1.y][tempCoord1.x]->Active())
            break;

        //중간에 빈 자리가 가다가 다음 카드와 변이 겹칠 때 (ㄱ자 연결)
        if (IsOnSameLine(tempCoord1, coord2))
            return true;

        POINT tempCoord2 = { x, coord2.y };

        //자기를 포함해서도 같은 변이 된다면... (ㄱ자 연결인데 비슷한 게 있다든가, 높이차가 1이라든가)
        if (IsOnSameLineIncludeSelf(tempCoord1, tempCoord2))
        {
            //다시 그 중 비슷한 카드와 다음 카드가 맞으면
            if (IsOnSameLine(coord2, tempCoord2))
                return true;
        }
    }

    for (int x = coord1.x - 1; x >= 0; --x)
    {
        POINT tempCoord1 = { x, coord1.y };

        if (cardBoard[tempCoord1.y][tempCoord1.x]->Active())
            break;

        //중간에 빈 자리가 가다가 다음 카드와 변이 겹칠 때 (ㄱ자 연결)
        if (IsOnSameLine(tempCoord1, coord2))
            return true;

        POINT tempCoord2 = { x, coord2.y };

        //자기를 포함해서도 같은 변이 된다면... (ㄱ자 연결인데 비슷한 게 있다든가, 높이차가 1이라든가)
        if (IsOnSameLineIncludeSelf(tempCoord1, tempCoord2))
        {
            //다시 그 중 비슷한 카드와 다음 카드가 맞으면
            if (IsOnSameLine(coord2, tempCoord2))
                return true;
        }
    }

    for (int y = coord1.y + 1; y < height; ++y)
    {
        POINT tempCoord1 = { coord1.x, y };

        if (cardBoard[tempCoord1.y][tempCoord1.x]->Active())
            break;

        //중간에 빈 자리가 가다가 다음 카드와 변이 겹칠 때 (ㄱ자 연결)
        if (IsOnSameLine(tempCoord1, coord2))
            return true;

        POINT tempCoord2 = { coord2.x, y };

        //자기를 포함해서도 같은 변이 된다면... (ㄱ자 연결인데 비슷한 게 있다든가, 높이차가 1이라든가)
        if (IsOnSameLineIncludeSelf(tempCoord1, tempCoord2))
        {
            //다시 그 중 비슷한 카드와 다음 카드가 맞으면
            if (IsOnSameLine(coord2, tempCoord2))
                return true;
        }
    }

    for (int y = coord1.y - 1; y >= 0; --y)
    {
        POINT tempCoord1 = { coord1.x, y };

        if (cardBoard[tempCoord1.y][tempCoord1.x]->Active())
            break;

        //중간에 빈 자리가 가다가 다음 카드와 변이 겹칠 때 (ㄱ자 연결)
        if (IsOnSameLine(tempCoord1, coord2))
            return true;

        POINT tempCoord2 = { coord2.x, y };

        //자기를 포함해서도 같은 변이 된다면... (ㄱ자 연결인데 비슷한 게 있다든가, 높이차가 1이라든가)
        if (IsOnSameLineIncludeSelf(tempCoord1, tempCoord2))
        {
            //다시 그 중 비슷한 카드와 다음 카드가 맞으면
            if (IsOnSameLine(coord2, tempCoord2))
                return true;
        }
    }

    //여기까지 오면 사방을 다 검사했는데 true가 안 나온 상황
    
    return false;
}

void MatchingScene::CheckMatchCard()
{
    // 짝을 맞춰서 결과를 찾아내기 (호출용)

    // 1. 선택한 카드 또 선택했을 때 그대로 종료
    // 2. 카드가 짝은 맞으면 진행 (카드의 유형은 같아야)

    if (!IsSameCard()) return; // 1, 2를 한 함수에서 싹 처리하고 함수 결과가 true여야 진행되게

    // 여기까지 왔으면 짝이 맞고, 두 장 카드를 다르게 선택했고
    // 3. 같은 변일 때
    if (IsOnSameLine(firstSelectedCard->GetCoord(), secondSelectedCard->GetCoord()))
    {
        //카드를 다 지우기
        firstSelectedCard->SetActive(false);
        secondSelectedCard->SetActive(false);
        return;
    }

    // 4. 변 높이는 다르지만 U자 모양으로 이어지는 게 가능할 때
    if (IsUTurn(firstSelectedCard->GetCoord(), secondSelectedCard->GetCoord()))
    {
        firstSelectedCard->SetActive(false);
        secondSelectedCard->SetActive(false);
        return; // 따지고 보면 필요는 없는데 나중에 뒤에 코드가 또 붙을 경우를 대비
    }
}

void MatchingScene::DeleteMatchCard()
{
    //카드 내부의 "선택됨" 변수 변경
    firstSelectedCard->Select(false); // 선택했던 카드의 선택 해제
    if (secondSelectedCard != nullptr) secondSelectedCard->Select(false);

    //씬 안에서도 포인터 빼기
    firstSelectedCard = nullptr;
    if (secondSelectedCard != nullptr) secondSelectedCard = nullptr;

    //위 계산이 끝난 후, 삭제 변수 리셋 (그래야 다음에 다시 삭제 가능)
    deleteTime = 0;
    isDeleteDelay = false;
}

void MatchingScene::SelectCard(void* card)
{
    // 카드를 클릭을 했을 때 일어날 일들

    // 완전히 틀린 입력을 했거나, 하나를 클릭하고 시간을 너무 오래 끌면
    // 선택된 것이 취소되도록 하고 싶다 (사천성 게임이면 보통 그러니까)

    if (isDeleteDelay) // 시간을 오래 끌었다 (혹은 다른 경우에도 이 옵션이 켜졌다)
    {
        DeleteMatchCard();
    }

    // 여기로 오면 정말로 잘 선택이 된 것

    Card* selectedCard = (Card*)card; // 매개변수를 카드로 형변환해서 쓴다
    selectedCard->Select(true); // 선택된 카드의 "선택됨" 변수를 true

    if (firstSelectedCard == nullptr)
    {
        firstSelectedCard = selectedCard; //첫 번째 카드 포인터 자리에 선택한 카드 할당
        return; //다 끝났으니 종료
    }
    //else if (secondSelectedCard == nullptr)
    //{
    //    secondSelectedCard = selectedCard;
    //}

    //위 코드 : 두 번째 포인터에도 할당하는 코드지만 아래 이유들로 인해서 안 쓰려고 합니다
    // 1. 위 코드를 쓰면 클릭을 잘못해서 한 번에 세 장, 네 장 카드를 후다닥 클릭했을 때 대응을 못 합니다
    // 2. ....어차피 짝 맞춰지면 즉시 비교를 해야 되는데 뭐 하러 굳이 "이 카드는 두 번째 칸으로 갈까 말까" 따질까요?
    // 그래서...

    secondSelectedCard = selectedCard; // 첫 번째 포인터가 할당이 됐으면, 두 번째는 따질 필요 없이 무조건 가장 최근에 고른 카드를 할당

    // 그리고 더 기다릴 필요 없이 즉시 짝 맞추기
    CheckMatchCard();

    //여기까지 오면 짝 맞추기를 다 했으니 삭제 관련 변수들도 리셋
    deleteTime = 0;
    //isDeleteDelay = true; //이걸 true로 만들어서, 카드 짝을 지우고, 해당 함수에서 이 변수 false로
    DeleteMatchCard(); // 혹은 그냥 곧장 삭제 함수를 호출해도 괜찮을 겁니다. (직접 호출이냐, 호출될 상황을 만드느냐 차이)
}

MatchingScene::EmptyDir MatchingScene::GetEmptyDir(POINT coord)
{
    EmptyDir result;

    //각 방향이 트여 있는가를 판별

    //오른쪽
    for (int x = coord.x + 1; x < width; ++x)
    {
        if (cardBoard[coord.y][x]->Active())
            result.right = false;
    }

    //왼쪽
    for (int x = coord.x - 1; x >= 0; --x)
    {
        if (cardBoard[coord.y][x]->Active())
            result.left = false;
    }

    //위쪽
    for (int y = coord.y + 1; y < height; ++y)
    {
        if (cardBoard[y][coord.x]->Active())
            result.up = false;
    }

    //아래쪽
    for (int y = coord.y - 1; y >= 0; --y)
    {
        if (cardBoard[y][coord.x]->Active())
            result.down = false;
    }

    // 여기까지 오면 true든 false든 각 좌표 주변의 상황이 들어온다
    // 해당 명제들의 구조체를 그대로 반환

    return result;
}