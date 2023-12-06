#include "Framework.h"
#include "FirstDHouseScene.h"

FirstDHouseScene::FirstDHouseScene()
{
	// 배경음악 등록
	Audio::Get()->Add("FirstBGM", "Sounds/DHouseSound/First_Menu_BGM.wav", true);
	Audio::Get()->Play("FirstBGM", 10.0f);

	// 포인터 인스턴스 등록
	firstdhouse = new FIrstDHouse();
}

FirstDHouseScene::~FirstDHouseScene()
{
	delete firstdhouse;
}

void FirstDHouseScene::Update()
{
	firstdhouse->Update();
}

void FirstDHouseScene::Render()
{
	firstdhouse->Render();
}

