#include "Framework.h"

Stage1::Stage1()
{
	stage2 = new Stage2();
	stage4 = new Stage4();
	stage5 = new Stage5();

	map = new Quad(L"Textures/DHouseTexure/Stage/Stage1.png");
	map->Pos() = { CENTER_X, CENTER_Y };
	map->UpdateWorld();

	objectALoad = new Quad(L"Textures/DHouseTexure/Stage/ObjectData/ObjectA #01.png");
	objectALoad->Pos() = { CENTER_X, CENTER_Y };
	objectALoad->UpdateWorld();

	noExit = new Quad(L"Textures/DHouseTexure/Stage/NoExit.png");
	noExit->Pos() = { CENTER_X, CENTER_Y };
	noExit->UpdateWorld();

	resultObject1 = new Quad(L"Textures/DHouseTexure/Stage/ObjectData/Object/Object1.png");
	resultObject1->Pos() = { CENTER_X, CENTER_Y };
	resultObject1->UpdateWorld();

	resultObject2 = new Quad(L"Textures/DHouseTexure/Stage/ObjectData/Object/Object2.png");
	resultObject2->Pos() = { CENTER_X, CENTER_Y };
	resultObject2->UpdateWorld();

	resultObject3 = new Quad(L"Textures/DHouseTexure/Stage/ObjectData/Object/Object3.png");
	resultObject3->Pos() = { CENTER_X, CENTER_Y };
	resultObject3->UpdateWorld();

	resultObject4 = new Quad(L"Textures/DHouseTexure/Stage/ObjectData/Object/Object4.png");
	resultObject4->Pos() = { CENTER_X, CENTER_Y };
	resultObject4->UpdateWorld();

	resultObject5 = new Quad(L"Textures/DHouseTexure/Stage/ObjectData/Object/Object5.png");
	resultObject5->Pos() = { CENTER_X, CENTER_Y };
	resultObject5->UpdateWorld();

	noObject1 = new Quad(L"Textures/DHouseTexure/Stage/ObjectData/NoObject/NoObject1.png");
	noObject1->Pos() = { CENTER_X, CENTER_Y };
	noObject1->UpdateWorld();

	noObject2 = new Quad(L"Textures/DHouseTexure/Stage/ObjectData/NoObject/NoObject2.png");
	noObject2->Pos() = { CENTER_X, CENTER_Y };
	noObject2->UpdateWorld();

	noObject3 = new Quad(L"Textures/DHouseTexure/Stage/ObjectData/NoObject/NoObject3.png");
	noObject3->Pos() = { CENTER_X, CENTER_Y };
	noObject3->UpdateWorld();

	noObject4 = new Quad(L"Textures/DHouseTexure/Stage/ObjectData/NoObject/NoObject4.png");
	noObject4->Pos() = { CENTER_X, CENTER_Y };
	noObject4->UpdateWorld();

	noObject5 = new Quad(L"Textures/DHouseTexure/Stage/ObjectData/NoObject/NoObject5.png");
	noObject5->Pos() = { CENTER_X, CENTER_Y };
	noObject5->UpdateWorld();
	
	// Left Top Collider
	wallMap["leftTop"] = new Wall(Vector2(950, 50));
	wallMap["leftTop"]->Scale() = { 1.0f, 1.0f };
	wallMap["leftTop"]->Pos() = { 50, 726 };

	// Left Top Side Collider
	wallMap["leftTopSide"] = new Wall(Vector2(200, 380));
	wallMap["leftTopSide"]->Scale() = { 1.0f, 1.0f };
	wallMap["leftTopSide"]->Pos() = { 1, 700 };

	// Left Bottom Collider
	wallMap["leftBottom"] = new Wall(Vector2(1050, 200));
	wallMap["leftBottom"]->Scale() = { 1.0f, 1.0f };
	wallMap["leftBottom"]->Pos() = { 1, 1 };

	// Left Bottom Side Collider
	wallMap["leftBottomSide"] = new Wall(Vector2(200, 200));
	wallMap["leftBottomSide"]->Scale() = { 1.0f, 1.0f };
	wallMap["leftBottomSide"]->Pos() = { 1, 200 };

	// Right Top Collider
	wallMap["rightTop"] = new Wall(Vector2(600, 50));
	wallMap["rightTop"]->Scale() = { 1.0f, 1.0f };
	wallMap["rightTop"]->Pos() = { 1055, 726 };

	// Right Top Side Collider
	wallMap["rightTopSide"] = new Wall(Vector2(300, 500));
	wallMap["rightTopSide"]->Scale()={1.0f, 1.0f};
	wallMap["rightTopSide"]->Pos() = { 1250, 760 };

	// Right Bottom Collider
	wallMap["rightBottom"] = new Wall(Vector2(600, 200));
	wallMap["rightBottom"]->Scale() = { 1.0f, 1.0f };
	wallMap["rightBottom"]->Pos() = { 1055, 1 };

	// Right Bottom Side Collider
	wallMap["rightBottomSide"] = new Wall(Vector2(300, 500));
	wallMap["rightBottomSide"]->Scale() = { 1.0f, 1.0f };
	wallMap["rightBottomSide"]->Pos() = { 1330, 50 };
	
	// Right Portal Collider
	wallMap["rightPortal"] = new Wall(Vector2(100, 300));
	wallMap["rightPortal"]->Scale() = { 1.0f, 1.0f };
	wallMap["rightPortal"]->Pos() = { 1305, 400 };

	// Left Portal Collider
	leftPortal_Area = new RectCollider(Vector2(100, 300));
	leftPortal_Area->Pos() = { 1, 400 };

	// Top Portal Collider
	topPortal_Area = new RectCollider(Vector2(100, 100));
	topPortal_Area->Pos() = { 620, 765 };

	// Right Portal Collider
	rightPortal_Area = new RectCollider(Vector2(100, 300));
	rightPortal_Area->Pos() = { 1300, 400 };

	// Bottom Portal Collider
	wallMap["bottomPortal"] = new Wall(Vector2(1000, 100));
	wallMap["bottomPortal"]->Scale() = { 1.0f, 1.0f };
	wallMap["bottomPortal"]->Pos() = { 650, 1 };

	bottomPortal_Area = new RectCollider(Vector2(1000, 100));
	bottomPortal_Area->Pos() = { 650, 10 };

	object1 = new RectCollider(Vector2(50, 50));
	object1->Pos() = { 130, 625 };

	player = new Player();
	player->Pos() = { CENTER_X, CENTER_Y };
	player->Scale() = { 1.5f, 1.5f };

	player->AddBlockObject(wallMap["leftTop"]->wall);
	player->AddBlockObject(wallMap["leftBottom"]->wall);
	player->AddBlockObject(wallMap["leftTopSide"]->wall);
	player->AddBlockObject(wallMap["leftBottomSide"]->wall);
	player->AddBlockObject(wallMap["rightTop"]->wall);
	player->AddBlockObject(wallMap["rightTopSide"]->wall);
	player->AddBlockObject(wallMap["rightBottom"]->wall);
	player->AddBlockObject(wallMap["rightBottomSide"]->wall);
	player->AddBlockObject(wallMap["rightPortal"]->wall);
	player->AddBlockObject(wallMap["bottomPortal"]->wall);
	
	object = false;
}

Stage1::~Stage1()
{
	delete map;

	// Left Portal Collider
	delete leftPortal_Area;

	// Top Portal Collider
	delete topPortal_Area;

	// RIght Portal Collider
	delete rightPortal_Area;

	// Bottom Portal Collider
	delete bottomPortal_Area;
	
	delete object1;
	delete objectALoad;
	delete player;
}

void Stage1::Update()
{
	// Left Portal Collider
	leftPortal_Area->UpdateWorld();

	// Top Portal Collider
	topPortal_Area->UpdateWorld();

	// RIght Portal Collider
	rightPortal_Area->UpdateWorld();
	
	// Bottom Portal Collider
	bottomPortal_Area->UpdateWorld();

	player->Update();

	wallMap["leftTop"]->Update();
	wallMap["leftBottom"]->Update();
	wallMap["leftTopSide"]->Update();
	wallMap["leftBottomSide"]->Update();
	wallMap["rightTop"]->Update();
	wallMap["rightTopSide"]->Update();
	wallMap["rightBottom"]->Update();
	wallMap["rightBottomSide"]->Update();
	wallMap["rightPortal"]->Update();
	wallMap["bottomPortal"]->Update();

	object1->UpdateWorld();

	if (player->characterArea->L() <= object1->R() &&
		player->characterArea->T() >= object1->B())
	{
		if (KEY_DOWN('G'))
		{
			PLAYERDATA->objectA = true;
			Active = true;

			Audio::Get()->Add("PaperLoad", "Sounds/DHouseSound/Paper-Sound-Effect.wav", false);
			Audio::Get()->Play("PaperLoad", 5.0f);
		}
	}

	if (player->characterArea->L() >= object1->R() ||
		player->characterArea->T() <= object1->B())
	{
		Active = false;
	}
	
	// Left Portal
	if (player->characterArea->L() <= leftPortal_Area->R())
	{
		SceneManager::Get()->ChangeScene("Stage2");
		
		// 문여는 소리
		Audio::Get()->Add("DoorOpen", "Sounds/DHouseSound/Door-open-sound-effect.wav", false);
		Audio::Get()->Play("DoorOpen", 10.0f);

		player->Pos() = { 100, 400 };
	}

	// Top Portal
	if (player->characterArea->T() >= topPortal_Area->B())
	{
		SceneManager::Get()->ChangeScene("Stage3");

		// 문여는 소리
		Audio::Get()->Add("DoorOpen", "Sounds/DHouseSound/Door-open-sound-effect.wav", false);
		Audio::Get()->Play("DoorOpen", 10.0f);

		player->Pos() = { 620, 600 };
	}

	// RIght Portal
	if (PLAYERDATA->objectA == true && PLAYERDATA->objectB == true&& PLAYERDATA->objectC == true && PLAYERDATA->objectD == true && PLAYERDATA->objectE == true)
	{
		if (player->characterArea->R() >= rightPortal_Area->L())
		{
			SceneManager::Get()->ChangeScene("Stage5");

			player->Pos() = { 1200, 400 };

			// 문여는 소리
			Audio::Get()->Add("DoorOpen", "Sounds/DHouseSound/Door-open-sound-effect.wav", false);
			Audio::Get()->Play("DoorOpen", 5.0f);
		}
	}
	else if (PLAYERDATA->objectA || PLAYERDATA->objectB || PLAYERDATA->objectC || PLAYERDATA->objectD || PLAYERDATA->objectE)
	{
		if (player->characterArea->R() >= rightPortal_Area->L())
		{
			SceneManager::Get()->ChangeScene("Stage4");

			player->Pos() = { 1200, 400 };

			Audio::Get()->Add("DoorOpen2", "Sounds/DHouseSound/Door-open-sound-effect.wav", false);
			Audio::Get()->Play("DoorOpen2", 1.0f);
		}
	}
	else if (PLAYERDATA->objectA == false && PLAYERDATA->objectB == false && PLAYERDATA->objectC == false && PLAYERDATA->objectD == false)
	{
		if (player->characterArea->R() >= rightPortal_Area->L())
		{
			Audio::Get()->Add("LockDoor", "Sounds/DHouseSound/Lock_Door_Sound_Effect.wav", false);
			Audio::Get()->Play("LockDoor", 1.0f);
		}
	}

	if (player->characterArea->B() <= bottomPortal_Area->T())
	{
		Active2 = true;

		Audio::Get()->Add("LockDoor", "Sounds/DHouseSound/Lock_Door_Sound_Effect.wav", false);
		Audio::Get()->Play("LockDoor", 1.0f);
	}
	else if (player->characterArea->B() >= bottomPortal_Area->T())
	{
		Active2 = false;
	}
}

void Stage1::Render()
{
	map->Render();

	// Left Portal Collider
	// leftPortal_Area->Render();

	// Top Portal Collider
	// topPortal_Area->Render();

	// RIght Portal Collider
	// rightPortal_Area->Render();

	// Bottom Portal Collider
	// wallMap["bottomPortal"]->Render();

	// Bottom Portal Collider
	// bottomPortal_Area->Render();
	
	// object1->Render();
	player->Render();

	// wallMap["leftTop"]->Render();
	// wallMap["leftBottom"]->Render();
	// wallMap["leftTopSide"]->Render();
	// wallMap["leftBottomSide"]->Render();
	// wallMap["rightTop"]->Render();
	// wallMap["rightTopSide"]->Render();
	// wallMap["rightBottom"]->Render();
	// wallMap["rightBottomSide"]->Render();
	// wallMap["rightPortal"]->Render();

	if (Active)
	{
		objectALoad->Render();
	}
	else if (!Active)
	{
		
	}

	if (Active2)
	{
		noExit->Render();
	}
	else if (!Active2)
	{

	}
}
