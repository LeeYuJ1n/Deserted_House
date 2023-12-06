#include "Framework.h"
#include "Hidden1Scene.h"

Hidden1Scene::Hidden1Scene()
{
	hidden1 = new Hidden1();
}

Hidden1Scene::~Hidden1Scene()
{
	delete hidden1;
}

void Hidden1Scene::Update()
{
	hidden1->Update();
}

void Hidden1Scene::Render()
{
	hidden1->Render();
}
