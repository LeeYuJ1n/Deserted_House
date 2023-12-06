#pragma once

class SceneManager : public Singleton<SceneManager>
{
private:
    friend class Singleton;

    SceneManager() = default;
    ~SceneManager();

public:

    void Update();

    void Render();
    void PreRender();
    void PostRender();

    void EndScene();
    void EndEveryScene();

    void Register(string key, Scene* scene);
    void ChangeScene(string key, bool init = true);

private:
    map<string, Scene*> scenes;

    Scene* curScene = nullptr;
};

