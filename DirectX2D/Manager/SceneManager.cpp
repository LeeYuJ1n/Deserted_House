#include "Framework.h"

SceneManager::~SceneManager()
{
    //맵에 있는 모든 씬을 종료한 다음에 지우기
    for (pair<string, Scene*> scene : scenes)
    {
        scene.second->Quit();
        delete scene.second;
    }
}

void SceneManager::Update()
{
    if (curScene == nullptr) return;

    curScene->Update();
}

void SceneManager::Render()
{
    if (curScene == nullptr) return;

    curScene->Render();
}

void SceneManager::PreRender()
{
    if (curScene == nullptr) return;

    curScene->PreRender();
}

void SceneManager::PostRender()
{
    if (curScene == nullptr) return;

    curScene->PostRender();
}

void SceneManager::Register(string key, Scene* scene)
{
    if (scenes.count(key) > 0) return;

    scenes[key] = scene;
}

void SceneManager::ChangeScene(string key, bool init)
{
    if (scenes.count(key) == 0) return;
    if (scenes[key] == curScene) return;

    if (curScene != nullptr && init)
    {
        //TODO : 초기화 사전작업 필요시 작성
    }

    curScene = scenes[key];

    if (init) curScene->Init();
}

void SceneManager::EndScene()
{
    if (curScene == nullptr) return;

    curScene->Quit();
}