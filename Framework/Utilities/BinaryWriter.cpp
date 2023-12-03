#include "Framework.h"

BinaryWriter::BinaryWriter(wstring filePath)
{

    // 윈도우에서 제공된 바이너리 출력 함수를 통해서 데이터를 파일에 담거나,
    // 데이터가 비었어도 미리 초기화된 파일을 작성

    file = CreateFile(filePath.c_str(), // 파일의 경로명
        GENERIC_WRITE,                  // 쓰기 권한 액서스
        0,                              // 공유 모드 (보통은 0)
        0,                              // 별도 보안 속성이 더 있을 경우 작성 (보통은 0)
        CREATE_ALWAYS,                  // 언제 파일을 만들 수 있느냐 (ALWAYS : 기존 파일이 있든 없든 무조건 만든다)
        FILE_ATTRIBUTE_NORMAL,          // 만들어진 파일의 OS 내 속성 설정 (읽기 전용 파일, 숨긴 파일.... 기본은 NORMAL[아무 속성 없음])
        nullptr);                       // 사전에 만들어진 파일 내용이 있는가?

    // 경로명 : (드라이브이름[생략가능]) + 폴더이름 + 파일이름

}

BinaryWriter::BinaryWriter(string filePath)
{
    file = CreateFileA(filePath.c_str(),
        GENERIC_WRITE,
        0,
        0,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        nullptr);
}

BinaryWriter::~BinaryWriter()
{
    // delete file;
    CloseHandle(file); // 위 코드와 역할은 같은데, 조금 더 안전
}

// 각 자료형에 따라 파일 작성
void BinaryWriter::Int(int data)
{
    // 작성 기능 자체는 윈도우에서 제공을 해준다 (대부분의 다른 프레임워크나 엔진도 마찬가지)
    WriteFile(file,  // 작성될 파일의 이름(혹은 경로명)
        &data,       // 어떤 데이터를 넣을 것인가? (=데이터의 메모리 내 위치)
        sizeof(int), // 한 데이터당 차지할 기준 크기
        &size,       // 총 파일 크기
        nullptr);     // 사전에 참조할 다른 파일 형식 등이 있는가? (보통은 nullptr)
}

void BinaryWriter::Float(float data)
{
    WriteFile(file, &data, sizeof(float), &size, nullptr);
}

void BinaryWriter::UInt(UINT data)
{
    WriteFile(file, &data, sizeof(UINT), &size, nullptr);
}

void BinaryWriter::String(string data)
{
    //위에 작성한 UInt를 써서 문자의 전체 정보(이 "문자의 벡터"는 총 몇 글자다)를 보존
    UInt(data.size()); // 여기 들어간  data = string = 문자의 벡터

    //클래스로 있던 스트링 데이터를 해체해서 문자열로 변환
    const char* str = data.c_str();

    WriteFile(file, str, sizeof(char) * data.size(), &size, nullptr);
    // string은 c++에서 쓰는 문자(char)의 배열이기 때문에 1차 기준 크기는 문자 하나(char)
    // 그런데 작성할 데이터는 string이므로 1차 기준에 문자 길이만큼 곱해서 실제 데이터의 기준크기를 도출
}

void BinaryWriter::Wstring(wstring data)
{
    UInt(data.size()); // 굳이 이런 호출로 파일에까지 정보를 넣는 이유 : 읽을 때도 쓰려고

    const WCHAR* str = data.c_str();
    WriteFile(file, str, sizeof(WCHAR) * data.size(), &size, nullptr);
}

void BinaryWriter::Byte(void* data, UINT dataSize)
{
    //무엇에든 대응해야 하므로 최대한 단순하게
    // -> 이 함수를 부를 때는 매개변수 넣는 쪽이(=호출 측이) 형변환부터 필요한 연산을 해두어야 한다

    WriteFile(file, data, dataSize, &size, nullptr);
}