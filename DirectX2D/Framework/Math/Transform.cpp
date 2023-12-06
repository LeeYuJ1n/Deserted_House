#include "Framework.h"

Transform::Transform()
{
    world = XMMatrixIdentity();
}

void Transform::UpdateWorld()
{
    S = XMMatrixScaling(localScale.x, localScale.y, 1.0f);
    R = XMMatrixRotationRollPitchYaw(localRotation.x,
        localRotation.y, localRotation.z);
    T = XMMatrixTranslation(localPosition.x, localPosition.y, 0.0f);
    
    P = XMMatrixTranslation(pivot.x, pivot.y, 0.0f);
    IP = XMMatrixInverse(nullptr, P);

    world = IP * S * R * T * P;

    if (parent)
        world *= parent->world;

    XMStoreFloat4x4(&matWorld, world);
    right = Vector2(matWorld._11, matWorld._12);
    up = Vector2(matWorld._21, matWorld._22);

    XMVECTOR outS, outR, outT;
    XMMatrixDecompose(&outS, &outR, &outT, world);

    Float2 tempPos, tempScale;
    XMStoreFloat2(&tempPos, outT);
    XMStoreFloat2(&tempScale, outS);

    globalPosition = tempPos;
    globalScale = tempScale;
}

void Transform::RenderUI()
{
    /*
    ImGui::Text(tag.c_str());

    string temp = tag + "_Pos";
    ImGui::DragFloat2(temp.c_str(), (float*)&localPosition, 1.0f);

    temp = tag + "_Rot";
    Float3 rot;
    rot.x = XMConvertToDegrees(localRotation.x);
    rot.y = XMConvertToDegrees(localRotation.y);
    rot.z = XMConvertToDegrees(localRotation.z);

    ImGui::DragFloat3(temp.c_str(), (float*)&rot, 1.0f, -180, 180);

    localRotation.x = XMConvertToRadians(rot.x);
    localRotation.y = XMConvertToRadians(rot.y);
    localRotation.z = XMConvertToRadians(rot.z);

    temp = tag + "_Scale";
    ImGui::DragFloat2(temp.c_str(), (float*)&localScale, 0.1f);
    */

    if (ImGui::TreeNode((tag + "_Transform").c_str()))
    {
        ImGui::Text(tag.c_str());

        string temp = tag + "_Pos";
        ImGui::DragFloat2(temp.c_str(), (float*)&localPosition, 1.0f);

        temp = tag + "_Rot";
        Float3 rot;
        rot.x = XMConvertToDegrees(localRotation.x);
        rot.y = XMConvertToDegrees(localRotation.y);
        rot.z = XMConvertToDegrees(localRotation.z);

        ImGui::DragFloat3(temp.c_str(), (float*)&rot, 1.0f, -180, 180);

        localRotation.x = XMConvertToRadians(rot.x);
        localRotation.y = XMConvertToRadians(rot.y);
        localRotation.z = XMConvertToRadians(rot.z);

        temp = tag + "_Scale";
        ImGui::DragFloat2(temp.c_str(), (float*)&localScale, 0.1f);

        if (ImGui::Button("Save"))
            Save();

        ImGui::SameLine();

        if (ImGui::Button("Load"))
            Load();

        ImGui::TreePop();
    }
}

bool Transform::Active()
{
    if (parent == nullptr)
        return isActive;

    if (isActive == false)
        return false;

    return parent->Active();
}

void Transform::Load()
{
    //파일에서 정보가 있을 경우 로딩 진행하기

    BinaryReader* reader = new BinaryReader("TextData/Transforms/" + tag + ".srt");
    // srt : 행렬 정보를 담은 확장자, ini : 범용 설정값. 윈도우에서 접근 가능하다는 의미도 포함

    //파일이 없으면 무시
    //if (!reader->IsValid()) return; // 파일이 "적절한 경우가" 아니면 리턴
    if (reader->IsFailed()) return; // 파일 읽기"에 실패했음이 true인 경우" 리턴

    //여기까지 오면 파일 읽기에 성공 - 진행
    // 위치, 회전, 크기 순으로 모두 읽는다

    localPosition.x = reader->Float();
    localPosition.y = reader->Float();
    //localPosition.z = reader->Float(); // 3D일 경우 이렇게 추가 필요

    localRotation.x = reader->Float();
    localRotation.y = reader->Float();
    localRotation.z = reader->Float();

    localScale.x = reader->Float();
    localScale.y = reader->Float();
    //localScale.z = reader->Float();

    delete reader;
}

void Transform::Save()
{
    BinaryWriter* writer = new BinaryWriter("TextData/Transforms/" + tag + ".srt");

    writer->Float(localPosition.x);
    writer->Float(localPosition.y);

    writer->Float(localRotation.x);
    writer->Float(localRotation.y);
    writer->Float(localRotation.z);

    writer->Float(localScale.x);
    writer->Float(localScale.y);

    delete writer;
}