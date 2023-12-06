#include "Framework.h"
#include "ClearHidden.h"

ClearHidden::ClearHidden()
{
	image = new Quad(L"Textures/DHouseTexure/Stage/Clear/Clear_Hidden.png");
	image->Pos() = { CENTER_X, CENTER_Y };
	image->UpdateWorld();
}

ClearHidden::~ClearHidden()
{
	delete image;
}

void ClearHidden::Update()
{
	if (KEY_DOWN('G'))
	{
		SceneManager::Get()->ChangeScene("Hidden1Scene");
	}
}

void ClearHidden::Render()
{
	image->Render();
}
