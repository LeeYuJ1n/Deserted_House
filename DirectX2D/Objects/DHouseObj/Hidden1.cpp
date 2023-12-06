#include "Framework.h"

Hidden1::Hidden1()
{
	image = new Quad(L"Textures/DHouseTexure/Stage/Clear/hidden.png");
	image->Pos() = { CENTER_X, CENTER_Y };
	image->UpdateWorld();

	image2 = new Quad(L"Textures/DHouseTexure/Stage/Clear/Hidden2.png");
	image2->Pos() = { CENTER_X, CENTER_Y };
	image2->UpdateWorld();

	image3 = new Quad(L"Textures/DHouseTexure/Stage/Clear/Hidden3.png");
	image3->Pos() = { CENTER_X, CENTER_Y };
	image3->UpdateWorld();

	count = 0;
}

Hidden1::~Hidden1()
{
	delete image;
}

void Hidden1::Update()
{
	if (KEY_DOWN('G'))
	{
		count++;
	}
	
	if (count == 3)
	{
		SceneManager::Get()->ChangeScene("Dhouse");

		Audio::Get()->Add("FirstBGM", "Sounds/DHouseSound/First_Menu_BGM.wav", true);
		Audio::Get()->Play("FirstBGM", 10.0f);
	}
}

void Hidden1::Render()
{
	if (count == 0)
	{
		image->Render();
	}
	else if (count == 1)
	{
		image2->Render();
	}
	else if (count == 2)
	{
		image3->Render();
	}
}
