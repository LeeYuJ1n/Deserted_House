#pragma once
class DijkstraScene : public Scene
{
public:
    //필수4종
    DijkstraScene();
    ~DijkstraScene();

    virtual void Update() override;
    virtual void Render() override;

    //옵션 중 초기화와 포스트렌더
    virtual void Init() override;
    virtual void PostRender() override;

private:

    Dijkstra* dijkstra;
    Tank* tank;

};

