#include "Framework.h"

Stage2::Stage2()
{
	map = new Quad(L"Textures/DHouseTexure/Stage/Stage2.png");
	map->Pos() = { CENTER_X, CENTER_Y };
	map->UpdateWorld();

	player = new Player();
	player->Pos() = { 1220, 200 };
	player->Scale() = { 1.5f, 1.5f };

	rightPortal_Area = new RectCollider(Vector2(50, 300));
	rightPortal_Area->Pos() = { 1300, 200 };

	object1 = new RectCollider(Vector2(50, 50));
	object1->Pos() = { 230, 105 };

	object2 = new RectCollider(Vector2(50, 50));
	object2->Pos() = { 370, 600 };

	objectBLoad = new Quad(L"Textures/DHouseTexure/Stage/ObjectData/ObjectB #02.png");
	objectBLoad->Pos() = { CENTER_X, CENTER_Y };
	objectBLoad->UpdateWorld();

	objectELoad = new Quad(L"Textures/DHouseTexure/Stage/ObjectData/ObjectE #05.png");
	objectELoad->Pos() = { CENTER_X, CENTER_Y };
	objectELoad->UpdateWorld();

	wallMap["left"] = new Wall(Vector2(100, 700));
	wallMap["left"]->Scale() = { 1.0f, 1.0f };
	wallMap["left"]->Pos() = { 150, 350 };

	wallMap["bottom"] = new Wall(Vector2(1300, 100));
	wallMap["bottom"]->Scale() = { 1.0f, 1.0f };
	wallMap["bottom"]->Pos() = { 700, 50 };

	wallMap["top"] = new Wall(Vector2(1300, 100));
	wallMap["top"]->Scale() = { 1.0f, 1.0f };
	wallMap["top"]->Pos() = { 700, 750 };

	wallMap["right"] = new Wall(Vector2(100, 600));
	wallMap["right"]->Scale() = { 1.0f, 1.0f };
	wallMap["right"]->Pos() = { 1235, 615 };

	player->AddBlockObject(wallMap["left"]->wall);
	player->AddBlockObject(wallMap["bottom"]->wall);
	player->AddBlockObject(wallMap["top"]->wall);
	player->AddBlockObject(wallMap["right"]->wall);
}

Stage2::~Stage2()
{	
	delete map;
	delete player;
	delete rightPortal_Area;
	delete objectBLoad;
	delete objectELoad;
	delete object1;
	delete object2;
}

void Stage2::Update()
{
	rightPortal_Area->UpdateWorld();
	object1->UpdateWorld();
	object2->UpdateWorld();

	wallMap["left"]->Update();
	wallMap["bottom"]->Update();
	wallMap["top"]->Update();
	wallMap["right"]->Update();

	if (player->characterArea->R() >= rightPortal_Area->L())
	{
		SceneManager::Get()->ChangeScene("Stage1");	

		// 문여는 소리
		Audio::Get()->Add("DoorOpen", "Sounds/DHouseSound/Door-open-sound-effect.wav", false);
		Audio::Get()->Play("DoorOpen", 10.0f);

		player->Pos() = { 1200, 200 };
	}

	if (player->characterArea->L() <= object1->R() &&
		player->characterArea->B() <= object1->T())
	{
		if (KEY_DOWN('G'))
		{
			PLAYERDATA->objectB = true;
			ActiveA = true;

			Audio::Get()->Add("PaperLoad", "Sounds/DHouseSound/Paper-Sound-Effect.wav", false);
			Audio::Get()->Play("PaperLoad", 5.0f);
		}
	}

	if (player->characterArea->L() >= object1->R() ||
		player->characterArea->B() >= object1->T())
	{
		ActiveA = false;
	}

	if (player->characterArea->L() <= object2->R() &&
		player->characterArea->T() >= object2->B())
	{
		if (KEY_DOWN('G'))
		{
			PLAYERDATA->objectE = true;
			ActiveE = true;

			Audio::Get()->Add("PaperLoad", "Sounds/DHouseSound/Paper-Sound-Effect.wav", false);
			Audio::Get()->Play("PaperLoad", 5.0f);
		}
	}

	if (player->characterArea->L() >= object2->R() ||
		player->characterArea->T() <= object2->B())
	{
		ActiveE = false;
	}

	player->Update();
}
void Stage2::Render()
{
	map->Render();
	player->Render();
	// rightPortal_Area->Render();
	// object1->Render();
	// object2->Render();

	// wallMap["left"]->Render();
	// wallMap["bottom"]->Render();
	// wallMap["top"]->Render();
	// wallMap["right"]->Render();

	if (ActiveA)
	{
		objectBLoad->Render();
	}
	else if (!ActiveA)
	{

	}

	if (ActiveE)
	{
		objectELoad->Render();
	}
	else if (!ActiveE)
	{

	}
}
