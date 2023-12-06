#include "Framework.h"

Card::Card(wstring textureFile)
    : Button(textureFile)
{
    key = textureFile; // 파일 이름을 바로 카드 이름으로 (이니셜라이저 가능)
                       // -> 이 카드 이름을 다른 곳에서 출력에 쓸 수 있도록 한다
                       //    + 게임에서는 이 카드 이름을 직접 쓸 생각이 없다

    SetPixelShader(L"Outline.hlsl");

    SetEvent(bind(&Card::OnClick, this));

    intBuffer = new IntValueBuffer();
    floatBuffer = new FloatValueBuffer();
    colorBuffer = new ColorBuffer();

    floatBuffer->Get()[0] = size.x;
    floatBuffer->Get()[1] = size.y;

    colorBuffer->Get() = { 1, 1, 0, 1 };
}

Card::~Card()
{
    delete intBuffer;
    delete floatBuffer;
    delete colorBuffer;
}

void Card::Update()
{
    //Button::Update();
    //선택이 되었을 때 생기는 카드 자체 변화
    // -> 셰이더에 넣을 값을 약간 변화
    if (isSelected) intBuffer->Get()[0] = 1;
    else intBuffer->Get()[0] = 0;

    Button::Update(); //윗줄 코드 반영용
}

void Card::Render()
{
    //셰이더 적용된 다른 사물 렌더하듯이...

    if (!isActive) return;

    intBuffer->SetPS(1);
    floatBuffer->SetPS(2);
    colorBuffer->SetPS(3); // 아웃라인 셰이더는 3

    Quad::Render();
}

void Card::OnClick()
{
    Observer::Get()->ExcuteParamEvent("SelectCard", this);
}