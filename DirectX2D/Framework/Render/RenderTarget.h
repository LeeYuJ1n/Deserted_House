#pragma once

class RenderTarget
{
public:
    RenderTarget(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
    ~RenderTarget();

    void Set(Float4 clearColor = Float4(1, 1, 1, 1)); //빼거나 더할 색을 포함해서 세팅 하기

    //셰이더 리소스 주고받기
    ID3D11ShaderResourceView* GetSRV() { return srv; }

private:
    //화소 정보 만들기
    void CreateRTVTexture();
    void CreateRTV();
    void CreateSRV();

    //렌더 정보의 가로 세로
    UINT width;
    UINT height;

    //렌더 타겟 화소 정보 (*다이렉트 x에 제공되는 함수가 있다)
    ID3D11Texture2D* rtvTexture; // 텍스처
    ID3D11RenderTargetView* rtv; // 렌더 타겟 뷰(값)
    ID3D11ShaderResourceView* srv; // 셰이더 리소스가 있을 경우 그 뷰(값)
};

