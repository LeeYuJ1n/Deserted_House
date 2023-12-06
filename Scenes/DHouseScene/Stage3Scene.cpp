#include "Framework.h"
#include "Stage3Scene.h"

Stage3Scene::Stage3Scene()
{
	stage3 = new Stage3();
}

Stage3Scene::~Stage3Scene()
{
	delete stage3;
}

void Stage3Scene::Update()
{
	stage3->Update();
}

void Stage3Scene::Render()
{
	stage3->Render();
}


