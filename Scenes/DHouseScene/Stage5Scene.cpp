#include "Framework.h"
#include "Stage5Scene.h"

Stage5Scene::Stage5Scene()
{
	stage5 = new Stage5();
}

Stage5Scene::~Stage5Scene()
{
	delete stage5;
}

void Stage5Scene::Update()
{
	stage5->Update();
}

void Stage5Scene::Render()
{
	stage5->Render();
}

