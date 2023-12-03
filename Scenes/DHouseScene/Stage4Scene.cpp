#include "Framework.h"
#include "Stage4Scene.h"

Stage4Scene::Stage4Scene()
{
	stage4 = new Stage4();
}

Stage4Scene::~Stage4Scene()
{
	delete stage4;
}

void Stage4Scene::Update()
{
	stage4->Update();
}
void Stage4Scene::Render()
{
	stage4->Render();
}


