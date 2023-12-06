#include "Framework.h"
#include "RenderTargetScene.h"

RenderTargetScene::RenderTargetScene()
{
    // 배경 작성
    background = new Quad(L"Textures/Shooting/backgraound.png");
    background->Pos() = {CENTER_X, CENTER_Y};
    background->Scale() = background->Scale() * 2;
    background->UpdateWorld();

    //비행기
    plane = new Plane();
    plane->Pos() = { CENTER_X, CENTER_Y };

    //렌더 타겟 인스턴스 생성
    renderTarget = new RenderTarget();

    Texture* texture = Texture::Add(L"Textures/blank.png", renderTarget->GetSRV());

    //렌더 타겟 정보를 실제로 출력할 텍스처
    Quad* renderTexture;
    renderTexture = new Quad(Vector2(WIN_WIDTH / 2, WIN_HEIGHT / 2));
    renderTexture->Pos() = { CENTER_X / 2, CENTER_Y / 2 };
    renderTexture->UpdateWorld();
    renderTexture->SetTexture(texture);

    //렌더 타겟 텍스처의 벡터에 넣기
    renderTextures.push_back(renderTexture);

    // 같은 변수를 쓰되 할당을 고쳐서 새 텍스처 또 만들기 (C++에서 cin으로 입력 바꿨던 것과 비슷한 원리)
    renderTexture = new Quad(Vector2(WIN_WIDTH / 2, WIN_HEIGHT / 2)); //크기는 첫 번째와 같이
    renderTexture->Pos() = { CENTER_X * 3 / 2, CENTER_Y / 2 }; // 위치를 첫 번째의 옆에 오도록
    renderTexture->UpdateWorld();
    renderTexture->SetTexture(texture);
    //이번 텍스처에 추가 픽셀 셰이더 적용하기
    renderTexture->SetPixelShader(L"Filter.hlsl");

    //렌더 타겟 텍스처의 벡터에 넣기
    renderTextures.push_back(renderTexture);

    //버퍼 만들기
    intBuffer = new IntValueBuffer();
    intBuffer->Get()[0] = 3;
    intBuffer->Get()[1] = 50;

    floatBuffer = new FloatValueBuffer();
    floatBuffer->Get()[0] = WIN_WIDTH;
    floatBuffer->Get()[1] = WIN_HEIGHT;
}

RenderTargetScene::~RenderTargetScene()
{
    delete background;
    delete plane;

    delete renderTarget;

    for (Quad* quad : renderTextures)
        delete quad;

    delete intBuffer;
    delete floatBuffer;
}

void RenderTargetScene::Update()
{
    plane->Update();
}

void RenderTargetScene::Render()
{
    // 렌더 타겟이 아니라면 여기서 (주) 렌더 수행
    // (온 화면에 나와야 되는 게 있다면 여기서 작성)
}

void RenderTargetScene::PreRender()
{
    // 여기 작성되는 코드들은 렌더 연산 전에 수행된다

    renderTarget->Set(); // 정보는 정본데 딱히 렌더 자체는 아닌, 업데이트라기도 애매한

    //배경과 비행기도 모니터에 실제 출력될 대상이 (이번에는) 아니다
    background->Render();
    plane->Render();
}

void RenderTargetScene::PostRender()
{
    // 렌더 타겟은 화면 분할 끝나고, 1차 출력 후에, 결과들 지연 출력
    // (화면이 나뉘어야 하면 여기서 출력)

    intBuffer->SetPS(1);   //필터와 다중셰이더
    floatBuffer->SetPS(2); //텍스처

    //렌더 타겟 출력
    for (Quad* renderTexture : renderTextures)
        renderTexture->Render();
}