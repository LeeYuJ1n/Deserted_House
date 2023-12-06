#include "Framework.h"
#include "Stage1Scene.h"

Stage1Scene::Stage1Scene()
{
	stage1 = new Stage1();
}

Stage1Scene::~Stage1Scene()
{
	delete stage1;
}

void Stage1Scene::Update()
{
	stage1->Update();
}

void Stage1Scene::Render()
{
	stage1->Render();
}

