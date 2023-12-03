#pragma once

class BinaryReader
{
public:

    //기본 형태는 라이터와 같다 (입출력만 반대)

    BinaryReader(string filePath);
    BinaryReader(wstring filePath);
    ~BinaryReader();

    // 데이터 치환용 함수 작성이 필요 : 2진법을 통한 파일 입출력은 진짜 0과 1만 쓰니까...
    int Int(); // void 대신 반환값 추가
    float Float();
    UINT UInt();
    string String();
    wstring Wstring();

    //2진 그대로 읽기만 예외
    void Byte(void** data, UINT dataSize);
    // void** data : 데이터(void*)가 들어갈 위치 (포인터의 포인터)
    // dataSize : 데이터 들어갈 자리 미리 지정


    // 리더 전용 함수 : "파일에서 데이터가 없었습니다"를 반환받기 위한 함수
    bool IsFailed() { return (file == INVALID_HANDLE_VALUE); } // 핸들링 결과가 없거나, 있어도 부적절하면 "실패" 함수가 true
    bool IsValid() { return (file != INVALID_HANDLE_VALUE); } // 위 함수와 똑같은데 아 다르고 어 다른 함수

private:

    //쓰기와 똑같은 변수 필요
    HANDLE file;
    DWORD size = 0;

};

