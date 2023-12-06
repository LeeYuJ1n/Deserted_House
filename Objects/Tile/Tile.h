#pragma once

class Tile : public Button
{
    // 타일 : 반복적으로 깔아서 배경이나 시각적 결과를 만들기 위한 단위 요소

    // 타일의 유형 : 모든 정보를 가진 타일이 하나하나 놓여서 그룹을 구성
    //              혹은, 자리는 정해져 있고, 그 자리에 속성 요소를 설정함으로써 의미를 지정

    // 버튼을 상속받으면서 그림 출력, 클릭에 의한 상호작용은 보장받았다

public:

    enum Type //이 타일의 현재 속성
    {
        BG, //=Background
        OBJ, //=Object
    };

    struct Data //이 타일의 세부 정보
    {
        wstring textureFile;
        Vector2 pos;
        float angle = 0.0f; //각도가 있으면 타일 하나로 최소 둘 이상의 다른 결과를 얻어낼 수도 있어서
        Type type = BG;     //기본 유형은 배경으로 (액션이나 RPG 같은 경우라면 OBJ가 더 적절할 수도)
    };

    Tile(Data data); //만들 때 이미 기본 정보가 필요한 만큼 들어가게...
    ~Tile();

    void SetTexture(wstring file);
    void SetAngle(float angle);

    Data GetData() { return data; }

private:

    Data data;
};

