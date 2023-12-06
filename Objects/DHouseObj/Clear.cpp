#include "Framework.h"

Clear::Clear()
{
	image = new Quad(L"Textures/DHouseTexure/Stage/Clear/Clear.png");
	image->Pos() = { CENTER_X, CENTER_Y };
	image->UpdateWorld();
}

Clear::~Clear()
{
	delete image;
}

void Clear::Update()
{
	if (KEY_DOWN(VK_LBUTTON) || KEY_DOWN('G'))
	{
		SceneManager::Get()->ChangeScene("Dhouse");

		Audio::Get()->Add("FirstBGM", "Sounds/DHouseSound/First_Menu_BGM.wav", true);
		Audio::Get()->Play("FirstBGM", 10.0f);
	}
}

void Clear::Render()
{
	image->Render();
}
