#include "Framework.h"

Stage5::Stage5()
{
	map = new Quad(L"Textures/DHouseTexure/Stage/Stage5.png");
	map->Pos() = { CENTER_X, CENTER_Y };
	map->UpdateWorld();

	leftPortal_Area = new RectCollider(Vector2(50, 300));
	leftPortal_Area->Pos() = { 10, 220 };

	topPortal_Area = new RectCollider(Vector2(300, 50));
	topPortal_Area->Pos() = { 800, 700 };

	player = new Player();
	player->Pos() = { 100, 220 };
	player->Scale() = { 1.5f, 1.5f };

	wallMap["left"] = new Wall(Vector2(700, 600));
	wallMap["left"]->Scale() = { 1.0f, 1.0f };
	wallMap["left"]->Pos() = { 366, 608 };

	wallMap["right"] = new Wall(Vector2(100, 700));
	wallMap["right"]->Scale() = { 1.0f, 1.0f };
	wallMap["right"]->Pos() = { 976, 450 };

	wallMap["bottom"] = new Wall(Vector2(900, 100));
	wallMap["bottom"]->Scale() = { 1.0f, 1.0f };
	wallMap["bottom"]->Pos() = { 500, 90 };

	player->AddBlockObject(wallMap["left"]->wall);
	player->AddBlockObject(wallMap["right"]->wall);
	player->AddBlockObject(wallMap["bottom"]->wall);
}

Stage5::~Stage5()
{
	delete map;
	delete player;
	delete leftPortal_Area;
	delete topPortal_Area;
}

void Stage5::Update()
{
	player->Update();
	map->UpdateWorld();
	leftPortal_Area->UpdateWorld();
	topPortal_Area->UpdateWorld();

	wallMap["left"]->Update();
	wallMap["right"]->Update();
	wallMap["bottom"]->Update();

	if (player->characterArea->L() <= leftPortal_Area->R())
	{
		// 문여는 소리
		Audio::Get()->Add("DoorOpen", "Sounds/DHouseSound/Door-open-sound-effect.wav", false);
		Audio::Get()->Play("DoorOpen", 5.0f);

		SceneManager::Get()->ChangeScene("Stage1");
	}

	if (player->characterArea->T() >= topPortal_Area->B())
	{
		// 문여는 소리
		Audio::Get()->Add("DoorOpen", "Sounds/DHouseSound/Door-open-sound-effect.wav", false);
		Audio::Get()->Play("DoorOpen", 5.0f);

		SceneManager::Get()->ChangeScene("ClearHidden");

		// player->Pos() = { 100, 600 };
		player->Pos() = { 100, 220 };
	}
}

void Stage5::Render()
{
	map->Render();
	player->Render();
	// leftPortal_Area->Render();
	// topPortal_Area->Render();

	// wallMap["left"]->Render();
	// wallMap["right"]->Render();
	// wallMap["bottom"]->Render();
}
