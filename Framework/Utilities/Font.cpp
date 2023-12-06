#include "Framework.h"

Font::Font()
{
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory), (IUnknown**)&writeFactory);

	D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory);
	
	IDXGIDevice* dxgiDevice;
	DEVICE->QueryInterface(&dxgiDevice);

	factory->CreateDevice(dxgiDevice, &device);

	device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS,
		&context);

	IDXGISurface* dxgiSurface;
	Device::Get()->GetSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (void**)&dxgiSurface);

	D2D1_BITMAP_PROPERTIES1 bp;
	bp.pixelFormat.format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
	bp.dpiX = 96;
	bp.dpiY = 96;
	bp.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
	bp.colorContext = nullptr;

	context->CreateBitmapFromDxgiSurface(dxgiSurface, &bp, &targetBitmap);

	context->SetTarget(targetBitmap);
}

Font::~Font()
{
	for (pair<string, ID2D1SolidColorBrush*> brush : brushes)
		brush.second->Release();

	for (pair<string, IDWriteTextFormat*> format : formats)
		format.second->Release();

	factory->Release();
	writeFactory->Release();
	targetBitmap->Release();
	context->Release();
	device->Release();
}

void Font::AddColor(string key, float r, float g, float b)
{
	if (brushes.count(key) > 0) return;

	ID2D1SolidColorBrush* brush = nullptr;

	D2D1::ColorF colorF(r, g, b);
	context->CreateSolidColorBrush(colorF, &brush);

	brushes[key] = brush;
}

void Font::AddStyle(string key, wstring font, float size, DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STYLE style, DWRITE_FONT_STRETCH stretch)
{
	if (formats.count(key) > 0) return;

	IDWriteTextFormat* format;

	writeFactory->CreateTextFormat(font.c_str(), nullptr,
		weight, style, stretch, size, L"ko", &format);

	formats[key] = format;
}

void Font::SetColor(string key)
{
	if (brushes.count(key) == 0) return;

	curBrush = brushes[key];
}

void Font::SetStyle(string key)
{
	if (formats.count(key) == 0) return;

	curFormat = formats[key];
}

void Font::RenderText(string text, Float2 pos, Float2 size, bool leftAlign)
{
	if (size.x == 0.0f && size.y == 0.0f)
	{
		size.x = text.size() * curFormat->GetFontSize();
		size.y = curFormat->GetFontSize();
	}

	Float2 halfSize = { size.x * 0.5f, size.y * 0.5f };

	pos.y = WIN_HEIGHT - pos.y;

	D2D1_RECT_F rectF;
	rectF.left = pos.x - halfSize.x;
	rectF.right = pos.x + halfSize.x;
	rectF.top = pos.y - halfSize.y;
	rectF.bottom = pos.y + halfSize.y;

	if (leftAlign) rectF.left += halfSize.x;
	if (leftAlign) rectF.right += halfSize.x;

	wstring temp = ChangeWString(text);

	context->DrawTextW(temp.c_str(), temp.size(),
		curFormat, &rectF, curBrush);
}

void Font::RenderText(wstring text, Float2 pos, Float2 size, bool leftAlign)
{
	if (size.x == 0.0f && size.y == 0.0f)
	{
		size.x = text.size() * curFormat->GetFontSize();
		size.y = curFormat->GetFontSize();
	}

	Float2 halfSize = { size.x * 0.5f, size.y * 0.5f };

	//매개변수와 상관없이 알아낼 수 있는 텍스트 크기에 따른 유동값
	Float2 tempSize = { text.size() * curFormat->GetFontSize() * 0.5f , curFormat->GetFontSize() * 0.5f };

	pos.y = WIN_HEIGHT - pos.y;

	//DX에서도 텍스트 출력하는 기본 방식은 비슷 (사각형을 만들고 거기에 텍스트 출력)
	D2D1_RECT_F rectF;
	rectF.left = pos.x - halfSize.x;
	rectF.right = pos.x + halfSize.x;
	rectF.top = pos.y - halfSize.y;
	rectF.bottom = pos.y + halfSize.y;

	// *환기 : 글자를 대화창에 출력할 때는 항상 배경부터 출력해야 합니다.

	//정렬 단락 예시 (아래 조건문을 응용하면 정렬 기능에 대해 힌트가 되어줄 겁니다)
	//정렬, 왼쪽 (*문자 배치를 오른쪽으로 당기기)
	if (leftAlign)
	{
		rectF.left += tempSize.x;
		rectF.right += tempSize.x; //창 오른쪽이 정해져야 한다면 이 줄 생략
		rectF.top -= pos.y - tempSize.y;
		rectF.bottom -= pos.y + tempSize.y; //창 아래쪽이 정해져야 한다면 이 줄 생략
	}

	context->DrawTextW(text.c_str(), text.size(),
		curFormat, &rectF, curBrush);
}

wstring Font::ChangeWString(string value)
{
	int nLen = MultiByteToWideChar(CP_ACP, 0, &value[0], value.size(), nullptr, 0);
	wstring strUni(nLen + 1, 0);
	int len = MultiByteToWideChar(CP_ACP, 0, value.c_str(), value.size(), &strUni[0], nLen);
	strUni[len] = 0;

	return strUni;
}
