#include "Framework.h"

Stage3::Stage3()
{
	map = new Quad(L"Textures/DHouseTexure/Stage/Stage3.png");
	map->Pos() = { CENTER_X, CENTER_Y };
	map->UpdateWorld();

	bottomPortal_Area = new RectCollider(Vector2(400, 100));
	bottomPortal_Area->Pos() = { 650, 30 };

	object1 = new RectCollider(Vector2(50, 50));
	object1->Pos() = { 300, 560 };

	object2 = new RectCollider(Vector2(50, 50));
	object2->Pos() = { 1140, 390 };

	player = new Player();
	player->Pos() = { 650, 200 };
	player->Scale() = { 1.5f, 1.5f };

	objectCLoad = new Quad(L"Textures/DHouseTexure/Stage/ObjectData/ObjectC #03.png");
	objectCLoad->Pos() = { CENTER_X, CENTER_Y };
	objectCLoad->UpdateWorld();

	objectDLoad = new Quad(L"Textures/DHouseTexure/Stage/ObjectData/ObjectD #04.png");
	objectDLoad->Pos() = { CENTER_X, CENTER_Y };
	objectDLoad->UpdateWorld();

	wallMap["top"] = new Wall(Vector2(1300, 100));
	wallMap["top"]->Scale() = { 1.0f, 1.0f };
	wallMap["top"]->Pos() = { 700, 735 };

	wallMap["left"] = new Wall(Vector2(100, 1300));
	wallMap["left"]->Scale() = { 1.0f, 1.0f };
	wallMap["left"]->Pos() = { 85, 500 };

	wallMap["right"] = new Wall(Vector2(100, 1300));
	wallMap["right"]->Scale() = { 1.0f, 1.0f };
	wallMap["right"]->Pos() = { 1233, 700 };

	wallMap["leftBottom"] = new Wall(Vector2(600, 100));
	wallMap["leftBottom"]->Scale() = { 1.0f, 1.0f };
	wallMap["leftBottom"]->Pos() = { 220, 110 };

	wallMap["rightBottom"] = new Wall(Vector2(600, 100));
	wallMap["rightBottom"]->Scale() = { 1.0f, 1.0f };
	wallMap["rightBottom"]->Pos() = { 1060, 110 };

	player->AddBlockObject(wallMap["top"]->wall);
	player->AddBlockObject(wallMap["left"]->wall);
	player->AddBlockObject(wallMap["right"]->wall);
	player->AddBlockObject(wallMap["leftBottom"]->wall);
	player->AddBlockObject(wallMap["rightBottom"]->wall);
}

Stage3::~Stage3()
{
	delete map;
	delete player;
	delete object1;
	delete object2;
	delete objectCLoad;
	delete objectDLoad;
}

void Stage3::Update()
{
	player->Update();
	bottomPortal_Area->UpdateWorld();
	object1->UpdateWorld();
	object2->UpdateWorld();

	wallMap["top"]->Update();
	wallMap["left"]->Update();
	wallMap["right"]->Update();
	wallMap["leftBottom"]->Update();
	wallMap["rightBottom"]->Update();

	if (player->characterArea->B() <= bottomPortal_Area->T())
	{
		SceneManager::Get()->ChangeScene("Stage1");

		// 문여는 소리
		Audio::Get()->Add("DoorOpen", "Sounds/DHouseSound/Door-open-sound-effect.wav", false);
		Audio::Get()->Play("DoorOpen", 10.0f);
	}

	if (player->characterArea->L() <= object1->R() &&
		player->characterArea->T() >= object1->B())
	{
		if (KEY_DOWN('G'))
		{
			PLAYERDATA->objectC = true;
			ActiveC = true;

			Audio::Get()->Add("PaperLoad", "Sounds/DHouseSound/Paper-Sound-Effect.wav", false);
			Audio::Get()->Play("PaperLoad", 5.0f);
		}
	}

	if (player->characterArea->L() >= object1->R() ||
		player->characterArea->T() <= object1->B())
	{
		ActiveC = false;
	}

	if (player->characterArea->R() >= object2->L() &&
		player->characterArea->T() >= object2->B())
	{
		if (KEY_DOWN('G'))
		{
			PLAYERDATA->objectD = true;
			ActiveD = true;

			Audio::Get()->Add("PaperLoad", "Sounds/DHouseSound/Paper-Sound-Effect.wav", false);
			Audio::Get()->Play("PaperLoad", 5.0f);
		}
	}

	if (player->characterArea->R() <= object2->L() ||
		player->characterArea->T() <= object2->B())
	{
		ActiveD = false;
	}
}

void Stage3::Render()
{
	map->Render();
	// bottomPortal_Area->Render();
	// object1->Render();
	// object2->Render();
	player->Render();

	// wallMap["top"]->Render();
	// wallMap["left"]->Render();
	// wallMap["right"]->Render();
	// wallMap["leftBottom"]->Render();
	// wallMap["rightBottom"]->Render();

	if (ActiveC)
	{
		objectCLoad->Render();
	}
	else if (!ActiveC)
	{

	}

	if (ActiveD)
	{
		objectDLoad->Render();
	}
	else if (!ActiveD)
	{

	}
}

