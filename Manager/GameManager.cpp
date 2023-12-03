#include "Framework.h"

#include "Scenes/TextureScene.h"
#include "Scenes/AnimationScene.h"
#include "Scenes/ShaderScene.h"
#include "Scenes/RenderTargetScene.h"
#include "Scenes/MatchingScene.h"
#include "Scenes/TileScene.h"
#include "Scenes/DijkstraScene.h"
#include "Scenes/TankScene.h"

// DHouse -> Scene
#include "Scenes/DHouseScene/FirstDHouseScene.h"
#include "Scenes/DHouseScene/EsterEggScene.h"
#include "Scenes/DHouseScene/Stage1Scene.h"
#include "Scenes/DHouseScene/Stage2Scene.h"
#include "Scenes/DHouseScene/Stage3Scene.h"
#include "Scenes/DHouseScene/Stage4Scene.h"
#include "Scenes/DHouseScene/Stage5Scene.h"

#include "Scenes/DHouseScene/ClearScene.h"
#include "Scenes/DHouseScene/ClearHidden.h"
#include "Scenes/DHouseScene/Hidden1Scene.h"

GameManager::GameManager()
{
    Create();

    uiViewBuffer = new MatrixBuffer();

    SCENE->Register("Plane", new TextureScene());
    SCENE->Register("Ninja", new AnimationScene());
    SCENE->Register("Shader", new ShaderScene());
    SCENE->Register("RTV", new RenderTargetScene());
    SCENE->Register("Match", new MatchingScene());
    SCENE->Register("Tile", new TileScene());
    SCENE->Register("PathFind1", new DijkstraScene());
    SCENE->Register("PathFind2", new TankScene());

    // DHouse -> SCENE
    SCENE->Register("Dhouse", new FirstDHouseScene());
    SCENE->Register("EsterEgg", new EsterEggScene());
    SCENE->Register("Stage1", new Stage1Scene());
    SCENE->Register("Stage2", new Stage2Scene());
    SCENE->Register("Stage3", new Stage3Scene());
    SCENE->Register("Stage4", new Stage4Scene());
    SCENE->Register("Stage5", new Stage5Scene());
    SCENE->Register("Clear", new ClearScene());
    SCENE->Register("ClearHidden", new ClearHidden());
    SCENE->Register("Hidden1Scene", new Hidden1Scene());

    SCENE->ChangeScene("Dhouse");
}

GameManager::~GameManager()
{
    SCENE->Delete();
    delete uiViewBuffer;

    Delete();
}

void GameManager::Update()
{
    //임시 : 씬 바꾸기
    // if (KEY_PRESS(VK_LSHIFT))
    // {
    //     if (KEY_DOWN('1'))
    //     {
    //         SCENE->ChangeScene("PathFind2"); //A* 씬
    //     }
    // 
    //     if (KEY_DOWN('2'))
    //     {
    //         SCENE->ChangeScene("Tile"); // 타일맵 바꾸기 (여기서 맵 작성하고 저장)
    //         // (필요하면 A* 씬에서 Init() 함수 지정해야 할 수도....)
    //     }
    // }


    // CAMERA->Update();

    Keyboard::Get()->Update();
    Timer::Get()->Update();

    SCENE->Update();
}

void GameManager::Render()
{
    SCENE->PreRender();
    
    Device::Get()->Clear();

    Font::Get()->GetDC()->BeginDraw();

    SCENE->Render();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
    Font::Get()->RenderText(fps, { 100, WIN_HEIGHT - 10 });

    // CAMERA->RenderUI(); // ImGUI 출력

    uiViewBuffer->SetVS(1);
    // SCENE->PostRender();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    Font::Get()->GetDC()->EndDraw();

    Device::Get()->Present();
}

void GameManager::Create()
{
    Keyboard::Get();
    Timer::Get();
    Device::Get();
    Environment::Get();
    Observer::Get();

    Font::Get()->AddColor("White", 1, 1, 1);
    Font::Get()->AddStyle("PGothic", L"맑은 고딕");

    Font::Get()->SetColor("White");
    Font::Get()->SetStyle("PGothic");

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Delete()
{
    Keyboard::Delete();
    Timer::Delete();
    Device::Delete();
    Shader::Delete();
    Texture::Delete();
    Environment::Delete();    
    Observer::Delete();
    Font::Delete();

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();

    ImGui::DestroyContext();
}
