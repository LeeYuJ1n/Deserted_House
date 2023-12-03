#pragma once

class TileScene : public Scene
{
public:

    TileScene();
    ~TileScene();

    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override; // ImGUI 사용 예정

    //추가된 함수 : 맵 세이브 로드
    void Save();
    void Load();

private:

    EditTileMap* editor; // 에디터 클래스
    vector<Button*> samples; // 에디터에서 불러 쓰기 위한 샘플자료들
    Quad* selected = nullptr; //현재 선택한 대상

    Vector2 sampleSize = { 50.0f, 50.0f };

    void ClickSample(void* sample); // 샘플을 클릭했을 때
    void CreateSamples(); // 샘플 처음 만들기


    //ImGUI에서 쓰기 위한 것들

    //타입지정(을 불러오기)
    Tile::Type selectedType = Tile::BG;

    //전체경로명(을 저장하기 위한 변수)
    string fullPath;
};

