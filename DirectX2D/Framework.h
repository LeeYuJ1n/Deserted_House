#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define WIN_START_X 100
#define WIN_START_Y 100

#define CENTER_X (WIN_WIDTH * 0.5f)
#define CENTER_Y (WIN_HEIGHT * 0.5f)

#define DEVICE Device::Get()->GetDevice()
#define DC Device::Get()->GetDeviceContext()

#define KEY_DOWN(k) Keyboard::Get()->Down(k)
#define KEY_UP(k) Keyboard::Get()->Up(k)
#define KEY_PRESS(k) Keyboard::Get()->Press(k)

#define DELTA Timer::Get()->GetElapsedTime()

#define SCENE SceneManager::Get()
#define CAMERA Environment::Get()->GetMainCamera()

//싱글턴 약어 매크로
#define PLAYERDATA PlayerData::Get()

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <functional>

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

//DirectXTex
#include <DirectXTex.h>
#pragma comment(lib, "DirectXTex.lib")

//DirectWrite
#include <d2d1_2.h>
#include <dwrite.h>

#include "Libraries/inc/fmod.hpp"
#pragma comment(lib, "Libraries/lib/fmod_vc.lib")

//ImGui
#include <ImGui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

//ImBui (Extended)
#include <dirent/dirent.h>
#include <ImGuiFileDialog.h>
#include <ImGuiFileDialogConfig.h>

#pragma comment(lib, "ImGui.lib")

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

using namespace std;
using namespace DirectX;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
typedef XMMATRIX Matrix;

typedef function<void()> Event;
typedef function<void(void*)> ParamEvent;
typedef function<void(int)> IntParamEvent;

//Framework Header

#include "Framework/Utilities/Singleton.h"
#include "Framework/Utilities/Keyboard.h"
#include "Framework/Utilities/Timer.h"
#include "Framework/Utilities/Utility.h"
#include "Framework/Utilities/Observer.h"
#include "Framework/Utilities/tinyxml2.h"
#include "Framework/Utilities/Font.h"
#include "Framework/Utilities/Audio.h"
#include "Framework/Utilities/GlobalEvent.h"
#include "Framework/Utilities/BinaryWriter.h"
#include "Framework/Utilities/BinaryReader.h"

using namespace Utility;

#include "Framework/Math/Vector2.h"
#include "Framework/Math/GameMath.h"
#include "Framework/Math/Transform.h"

using namespace GameMath;

#include "Framework/System/Device.h"

#include "Framework/Shader/Shader.h"
#include "Framework/Shader/VertexShader.h"
#include "Framework/Shader/PixelShader.h"

#include "Framework/Buffer/VertexBuffer.h"
#include "Framework/Buffer/IndexBuffer.h"
#include "Framework/Buffer/ConstBuffer.h"
#include "Framework/Buffer/VertexLayouts.h"
#include "Framework/Buffer/GlobalBuffer.h"

#include "Framework/Render/Texture.h"
#include "Framework/Render/Frame.h"
#include "Framework/Render/Clip.h"
#include "Framework/Render/RenderTarget.h"

#include "Framework/Collision/Collider.h"
#include "Framework/Collision/RectCollider.h"
#include "Framework/Collision/CircleCollider.h"
#include "Framework/Collision/LineCollider.h"

// #include "Framework/Environment/Camera.h"
#include "Framework/Environment/Environment.h"

//Algorithm Header
#include "Algorithm/DNode.h"
#include "Algorithm/Dijkstra.h"

#include "Algorithm/Node.h"
#include "Algorithm/Heap.h"
#include "Algorithm/AStar.h"

//Object Header
#include "Objects/Basic/GameObject.h"
#include "Objects/Basic/Quad.h"
#include "Objects/Basic/Action.h"
#include "Objects/Basic/Effect.h"

#include "Objects/UI/Button.h"

#include "Objects/Shooting/Plane.h"
#include "Objects/Shooting/Bullet.h"
#include "Objects/Shooting/Tank.h"

#include "Objects/Character/Ninja/Ninja.h"
#include "Objects/Character/Ninja/NinjaRun.h"
#include "Objects/Character/Ninja/NinjaJump.h"
#include "Objects/Character/Ninja/NinjaJumpUp.h"
#include "Objects/Character/Ninja/NinjaJumpDown.h"
#include "Objects/Character/Ninja/NinjaAttack.h"
#include "Objects/Character/Ninja/NinjaMeleeAttack.h"
#include "Objects/Character/Ninja/NinjaJumpAttack.h"
#include "Objects/Character/Ninja/NinjaThrow.h"
#include "Objects/Character/Ninja/NinjaJumpThrow.h"
#include "Objects/Character/Ninja/NinjaGlide.h"

#include "Objects/Card/Card.h"

#include "Objects/Tile/Tile.h"
#include "Objects/Tile/EditTileMap.h"
#include "Objects/Tile/GameTileMap.h"

// [ DHouse ] Objects -> DHouseChar
#include "Objects/DHouseChar/Player.h"
#include "Objects/DHouseChar/PlayerWalk.h"
#include "Objects/DHouseChar/PlayerDead.h"
#include "Objects/DHouseChar/PlayerData.h"

// [ DHouse ] Objects -> DHouseObj
#include "Objects/DHouseObj/FIrstDHouse.h"
#include "Objects/DHouseObj/EsterEgg.h"
#include "Objects/DHouseObj/Wall.h"

// [ DHouse ] Objects -> DhouseObj -> Stage
#include "Objects/DHouseObj/Stage/Stage1.h"
#include "Objects/DHouseObj/Stage/Stage2.h"
#include "Objects/DHouseObj/Stage/Stage3.h"
#include "Objects/DHouseObj/Stage/Stage4.h"
#include "Objects/DHouseObj/Stage/Stage5.h"
#include "Objects/DHouseObj/Hidden1.h"

#include "Objects/DHouseObj/Clear.h"

//Scene Header
#include "Scenes/Scene.h"
#include "Manager/GameManager.h"
#include "Manager/EffectManager.h"
#include "Manager/BulletManager.h"
#include "Manager/CommandManager.h"
#include "Manager/SceneManager.h"

extern HWND hWnd;
extern Vector2 mousePos;
extern float mouseWheel;