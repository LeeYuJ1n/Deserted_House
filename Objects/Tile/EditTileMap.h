#pragma once

class EditTileMap : public Transform
{
    // 타일을 배치해서 지도 만들기 + 앱 내에서 편집하기

    // 내부에 위치 정보가 있는 멤버들이 있어야 하므로, 자기 자신도 공간을 가지도록 한다
    // -> 공간 내 하위 공간 그룹으로 하나의 거대한 집합을 만드는 건 엔진 가서도 꼭 필요한 기법

public:
    EditTileMap(UINT width, UINT height);
    ~EditTileMap();

    void Update();
    void Render();

    //타일을 클릭했을 때 일어날 일들
    void ClickTile(Quad* selected, Tile::Type type);
    void DeleteObjTile();

    //편집한 결과를 세이브, 로드하기 위한 함수
    void Save(string file);
    void Load(string file);

private:

    UINT width;
    UINT height;

    //타일들의 벡터 (배경 따로 오브젝트 따로)
    vector<Tile*> bgTiles;
    vector<Tile*> objTiles;

    Vector2 tileSize; //타일 크기 기준 (타일마다 크기가 100% 같으란 법은 없지만, 100% 같을 때 에디터의 효용이 극대화)

    void CreateTiles();

    void SetBGTiles(wstring file, float angle); // 텍스처 파일은 탐색기에서 바로 읽을 거라서 wstring
    void SetOBJTiles(wstring file, float angle);

};

