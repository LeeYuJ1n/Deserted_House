#include "Framework.h"
#include "Stage2Scene.h"

Stage2Scene::Stage2Scene()
{
	stage2 = new Stage2();
}

Stage2Scene::~Stage2Scene()
{
	delete stage2;
}

void Stage2Scene::Update()
{
	stage2->Update();
}

void Stage2Scene::Render()
{
	stage2->Render();
}

