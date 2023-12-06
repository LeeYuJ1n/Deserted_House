#include "Framework.h"
#include "EsterEggScene.h"

EsterEggScene::EsterEggScene()
{
	esterEgg = new EsterEgg();
}

EsterEggScene::~EsterEggScene()
{
	delete esterEgg;
}

void EsterEggScene::Update()
{
	esterEgg->Update();
}

void EsterEggScene::Render()
{
	esterEgg->Render();
}


