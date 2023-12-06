#include "Framework.h"
#include "TileScene.h"

TileScene::TileScene()
{
    //샘플 만들기 호출
    CreateSamples();

    editor = new EditTileMap(10, 10); // 에디터 생성
    editor->Pos() = { 80, 80 };

    //현재 선택된 샘플의 기본 형태("선택이 안 되었을 때의 샘플")
    // -> 단위형태를 미리 주고 나중에 텍스처라든가 다른 정보만 바꾸면 더 빠르니까
    // -> (클릭할 때 그때그때 인스턴스를 만든다는 선택도 가능은 하다는 뜻)

    selected = new Quad(sampleSize); // 그림이 아닌 크기로 쿼드 일단 만들기

    char path[128];
    GetCurrentDirectoryA(sizeof(path), path);
    fullPath = path;
}

TileScene::~TileScene()
{
    delete selected;
    for (Button* button : samples)
        delete button;

    delete editor;
}

void TileScene::Update()
{
    // 나뉘어서 구현된 기능들을 여기서 끌어온다

    // 1. 타일을 클릭했을 때 일어날 일
    if (KEY_PRESS(VK_LBUTTON) && !ImGui::GetIO().WantCaptureMouse)
    {
        if (selected->GetTexture())
        {
            editor->ClickTile(selected, selectedType);
        }
    }

    if (KEY_DOWN(VK_RBUTTON) && !ImGui::GetIO().WantCaptureMouse)
    {
        editor->DeleteObjTile();
    }

    // 2. (옵션) 포스트렌더가 보류 중일 때 쓸 수 있는 키 입력을 통한 호출
    if (KEY_DOWN(VK_F5))
        editor->Save("TextData/Test.map");

    if (KEY_DOWN(VK_F9))
        editor->Load("TextData/Test.map");

    //버튼과 타일(에디터) 업데이트

    for (Button* button : samples)
        button->Update();

    editor->Update();

    //만약 선택된 샘플이 있다면......

    if (selected->GetTexture() != nullptr)
    {
        // 마우스 휠 입력이 잘 안 될 경우 확인 가능한 무식한 키입력식
        if (KEY_DOWN('Q'))
        {
            selected->Rot().z += XM_PIDIV2; //반지름의 원주율 곱을 2로 나누면? -> 90도!

            //각도가 360도 내에서 고정이 되도록
            if (selected->Rot().z > XM_2PI)
                //selected->Rot().z -= XM_2PI; // 360도 빼기 (순환)
                selected->Rot().z = XM_2PI; //360도로 맞추기 (최대값 고정)
        }

        if (KEY_DOWN('E'))
        {
            selected->Rot().z -= XM_PIDIV2;

            if (selected->Rot().z < 0)
                //selected->Rot().z += XM_2PI; // 360도 더하기 (순환)
                selected->Rot().z = 0.0f; //0도로 맞추기 (최소값 고정)
        }

        //마우스 휠 입력에 의해.....
        if (mouseWheel > 0.0f)
        {
            // 선택된 샘플을 회전!

            selected->Rot().z += XM_PIDIV2; //반지름의 원주율 곱을 2로 나누면? -> 90도!

            //각도가 360도 내에서 고정이 되도록
            if (selected->Rot().z > XM_2PI)
                //selected->Rot().z -= XM_2PI; // 360도 빼기 (순환)
                selected->Rot().z = XM_2PI; //360도로 맞추기 (최대값 고정)
        }
        else if (mouseWheel < 0.0f)
        {
            selected->Rot().z -= XM_PIDIV2;

            if (selected->Rot().z < 0)
                //selected->Rot().z += XM_2PI; // 360도 더하기 (순환)
                selected->Rot().z = 0.0f; //0도로 맞추기 (최소값 고정)
        }

        selected->Pos() = mousePos;
        selected->UpdateWorld();
    }
}

void TileScene::Render()
{
    for (Button* button : samples)
        button->Render();

    editor->Render();

    if (selected->GetTexture() != nullptr)
        selected->Render();
}

void TileScene::PostRender()
{
    const char* list[] = { "BG", "OBJ" };
    ImGui::ListBox("Type", (int*)&selectedType, list, 2);

    Save();
    Load();
}

void TileScene::ClickSample(void* sample)
{
    Button* button = (Button*)sample; // 매개변수를 버튼으로 다시 형변환
    
    //현재 선택된 버튼(이라는 이름의 변수) 내용을 클릭한 버튼 내용으로 바꾸기
    selected->SetTexture(button->GetTexture()); //텍스처 교체
}

void TileScene::CreateSamples()
{
    // 파일 핸들러 임시로 만들기 (카드 만들 때처럼)

    WIN32_FIND_DATA findData;
    HANDLE handle = FindFirstFile(L"Textures/Tile/*.png", &findData);

    bool result = true; // 불 변수 미리 true로 작성
    wstring filename;   // 파일 이름

    UINT width = 10;
    Vector2 size(sampleSize); // 기준 크기도 만들기
    Vector2 startPos(WIN_WIDTH - size.x, WIN_HEIGHT - size.y); //기준만큼 공백을 주고 만들기 (우측 정렬)

    while (result) // 위에서 만든 변수가 참인 동안
    {
        filename = L"Textures/Tile/";
        filename += findData.cFileName;

        // 남은 파일이 있는가? (있으면 등록, 없으면 bool 값 false)
        result = FindNextFile(handle, &findData);

        //파일 이름 도출과 다음 파일 여부 확인
        // -> 여기서부터는 도출된 파일 이름에서 정보 찾아 반영하기

        //샘플이 가야 할 관념상의 순번
        UINT index = samples.size(); // 현재 쌓인 벡터 크기 = 다음 번 순번
                                     // 항상 마지막 순번으로 들어가도록

        //샘플이 가야 할 위치 (순번에서 규칙적 배치)
        Vector2 pos(index % width, index / width); // 1중 벡터를 가로 세로로 나타낼 때 흔히 쓰는 방식

        Button* button = new Button(size); //크기로 버튼 만들기
        button->SetTexture(filename); //크기부터 만들고 크기에 텍스처 맞추기
        button->Pos() = startPos - (pos * size); // 기준 시작 지점 - (샘플이 가야 할 좌표 * 기준크기)
        button->SetParamEvent(bind(&TileScene::ClickSample, this, placeholders::_1)); //매개변수 있는 함수에 클릭 함수 할당
        button->SetObject(button); //고정 대상에 자기 자신 등록

        samples.push_back(button); //벡터에 만든 버튼 추가하기
    }

    // 여기까지 오면 벡터에 샘플은 다 넣은 셈
}

void TileScene::Save()
{
    if (ImGui::Button("Save"))
        ImGuiFileDialog::Instance()->OpenDialog("Save", "SaveFile", ".map", ".");

    if (ImGuiFileDialog::Instance()->Display("Save"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            string file = ImGuiFileDialog::Instance()->GetFilePathName();
            file = file.substr(fullPath.length() + 1);

            editor->Save(file);
        }

        ImGuiFileDialog::Instance()->Close();
    }
}

void TileScene::Load()
{
    if (ImGui::Button("Load"))
        ImGuiFileDialog::Instance()->OpenDialog("Load", "LoadFile", ".map", ".");

    if (ImGuiFileDialog::Instance()->Display("Load"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            string file = ImGuiFileDialog::Instance()->GetFilePathName();
            file = file.substr(fullPath.length() + 1);

            editor->Load(file);
        }

        ImGuiFileDialog::Instance()->Close();
    }
}