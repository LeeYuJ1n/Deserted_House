#include "Framework.h"
#include "ClearScene.h"

ClearScene::ClearScene()
{
	clear = new Clear();
}

ClearScene::~ClearScene()
{
	delete clear;
}

void ClearScene::Update()
{
	clear->Update();
}

void ClearScene::Render()
{
	clear->Render();
}
