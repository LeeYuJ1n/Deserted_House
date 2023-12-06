#pragma once

class Card : public Button
{
    // 버튼 기능의 확장 : 클릭과 상호작용 가능한 2D 사물 (현재 카드 형태)
    //                   지금은 카드지만 클래스 이름이 바뀌면 "유닛" "아이템"으로도 사용 가능

public:
    Card(wstring textureFile);
    ~Card();

    void Update();
    void Render();

    //카드에 기대할 만한 다른 함수가 있으면 작성
    
    //위치(좌표) 겟터, 셋터
    POINT GetCoord() { return coord; }
    void SetCoord(POINT coord) { this->coord = coord; }
    void SetCoord(int x, int y) { this->coord = { x, y }; }

    //선택 여부 토글
    void Select(bool value) { isSelected = value; }

    //키 받기
    wstring GetKey() { return key; }

private:
    void OnClick(); // 클릭하면 수행할 함수 (이벤트)

    //변수들 : 상호 작용 가능한, 선택 가능한, 버튼 기능을 갖춘, 2D 오브젝트에 필요한 것들

    //카드의 이름
    wstring key;

    //이 카드를 배치를 하려므로 배치할 곳의 위치
    POINT coord; // coord : "이 카드는 직사각형으로 같은 카드끼리 배치할 거고, 행렬의 형태를 띨 것이다"라는 예고
                 // -> 카드를 행렬처럼 배치한 후 클릭하는 게임을 만들 예정

    IntValueBuffer* intBuffer;
    FloatValueBuffer* floatBuffer;
    ColorBuffer* colorBuffer;

    //이 카드를 지금 선택을 했습니까?
    bool isSelected = false;
};

