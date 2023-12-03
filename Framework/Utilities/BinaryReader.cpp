#include "Framework.h"

BinaryReader::BinaryReader(string filePath)
{
    // 파일에 대한 정보(파일 자체든, 파일에 대한 메모리 내 정보든)
    // -> 파일을 다룰 때는 빠뜨릴 수 없는 부분

    file = CreateFileA(filePath.c_str(),
        GENERIC_READ,            // 읽기가 가능할 때 읽기
        FILE_SHARE_READ,         // 파일과 별개로 저장소에도 읽기 권한이 있어야 읽기
        0,
        OPEN_EXISTING,           // 언제 읽을 것인가? (ALWAYS : 없어도 만들어서 읽는다! / EXISTING : 있으면 읽는다)
        FILE_ATTRIBUTE_NORMAL,
        nullptr);
}

BinaryReader::BinaryReader(wstring filePath)
{
    file = CreateFile(filePath.c_str(),
        GENERIC_READ,            
        FILE_SHARE_READ,         
        0,
        OPEN_EXISTING,           
        FILE_ATTRIBUTE_NORMAL,
        nullptr);
}

BinaryReader::~BinaryReader()
{
    CloseHandle(file);
}

// 여기까지 파일 정보 읽기, 아래는 데이터 치환

int BinaryReader::Int()
{
    int result;

    // ReadFile : WriteFile에 대응하는 윈도우 제공 함수
    ReadFile(file, &result, sizeof(int), &size, nullptr);

    //위 함수 호출 후 result에 파일 값이 들어간다
    return result;
}

float BinaryReader::Float()
{
    float result;

    ReadFile(file, &result, sizeof(float), &size, nullptr);

    return result;
}

UINT BinaryReader::UInt()
{
    UINT result;

    ReadFile(file, &result, sizeof(UINT), &size, nullptr);

    return result;
}

string BinaryReader::String()
{
    UINT strSize = UInt(); // 파일에서 문자 크기 읽기

    //문자의 배열을 담기 위한 temp 문자열
    char* temp = new char[strSize + 1];

    ReadFile(file, temp, sizeof(char) * strSize, &size, nullptr);
    temp[strSize] = '\0';
    // 문자열이 현재의 c나 cpp에서 다뤄지려면 문자열의 끝이 "문자열 끝났다"는 특수문자여야 한다
    // 그렇기 때문에 이런 식으로 문자 배열에 거꾸로 값을 넣었을 때는, 배열의 끝을 "\0(문자 끝)"이라고 작성해서 문자열로서 쓰일 수 있도록 하는 것

    //이렇게 문자열로써 쓸 수 있는 데이터가 완성
    return (string)temp;
}

wstring BinaryReader::Wstring()
{
    UINT strSize = UInt();

    WCHAR* temp = new WCHAR[strSize + 1];
    ReadFile(file, temp, sizeof(WCHAR) * strSize, &size, nullptr);
    temp[strSize] = '\0';

    return (wstring)temp;
}

void BinaryReader::Byte(void** data, UINT dataSize)
{
    ReadFile(file, *data, dataSize, &size, nullptr);
    //전달된 매개변수 *data = void** data의 실제 대상을 뜻한다
    //=> *(&&data)나 다름없다 = &data, (void*) data라는 뜻
}