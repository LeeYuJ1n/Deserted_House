#pragma once

class TankScene : public Scene
{
    //씬 클래스 필수 4종

public:
    TankScene();
    ~TankScene();

    virtual void Update() override;
    virtual void Render() override;

    // + 필요하면 옵션 (포스트렌더, 프리렌더, 이니시에이션, 큇)
    virtual void Init() override; //시작과 종료가 필요하다면
    virtual void Quit() override;

    virtual void PreRender() override; // 이펙트 적용 등의 추가 출력이 필요하다면
    virtual void PostRender() override; //디버그 UI 표시 등의 추가 안내가 필요하다면

private:

    GameTileMap* gameTileMap; // 타일 씬에서 만든 타일 배치를 쓰기 위한 클래스
    
    AStar* aStar; // 길 찾기 알고리즘 (핵심)

    Tank* tank; //탱크 (플레이어)
};

