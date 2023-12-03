#include "Framework.h"

// 가로 세로(혹시 나중에 다른 설정이 개입한다면, 그것까지)에 의해서 만들어지는
// 표적 지정 렌더 정보 (특정한 대상만 특정한 방식으로 표현한다)

RenderTarget::RenderTarget(UINT width, UINT height)
    : width(width), height(height)
{
    // 의도를 밝힌다면 아래(직접 할당), 효율을 위한다면 위(이니셜라이저)
    // this->width = width;
    // this->height = height;

    CreateRTVTexture();
    CreateRTV();
    CreateSRV();
}

RenderTarget::~RenderTarget()
{
    rtvTexture->Release();
    rtv->Release();
}

void RenderTarget::Set(Float4 clearColor)
{
    DC->OMSetRenderTargets(1, &rtv, nullptr);
    DC->ClearRenderTargetView(rtv, (float*)&clearColor);
}

void RenderTarget::CreateRTVTexture()
{
    // 기본 렌더를 위해서는 출력을 위한 사전 설정 후, 자료를 받는다(연산 수행)
    // 렌더 타겟을 위해서는 자료를 받은 후, 실질 출력 정보를 설정한다

    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1; // 밉 맵의 수준, 1 = "기본 수준 = 기본 크기"를 뜻한다
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;

    //만든 정보를 바탕으로 2D 텍스처 재가공 후 rtv텍스처에 반영
    DEVICE->CreateTexture2D(&desc, nullptr, &rtvTexture);
}

// 렌더 타겟을 위한 추가적인 정보 생성, 반영

void RenderTarget::CreateRTV()
{
    D3D11_RENDER_TARGET_VIEW_DESC desc = {};
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

    DEVICE->CreateRenderTargetView(rtvTexture, &desc, &rtv);
}

void RenderTarget::CreateSRV()
{
    D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    desc.Texture2D.MipLevels = 1;

    DEVICE->CreateShaderResourceView(rtvTexture, &desc, &srv);
}