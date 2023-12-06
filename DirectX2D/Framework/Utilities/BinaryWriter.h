#pragma once
class BinaryWriter
{
public:

    BinaryWriter(wstring filePath); // <- 각 탐색기와 쉽게 연계 가능
    BinaryWriter(string filePath);  // <- C++ 안에서 쓰기 좋다 (+영문 윈도우와도 좋지만, 한국인에게는 별 의미 없는 장점...)
    ~BinaryWriter();

    // 코드 연산에 의해 자료가 발생하면, 해당 자료형에 맞추어서 곧바로 파일을 작성하는 함수
    void Int(int data); //<- 어떤 식으로든 한번 데이터가 형변환되어서 들어가야, 형변환된 데이터를 다시 사용가능 (원래 정수였든, 중간에 형변환을 했든...)
    void Float(float data);
    void UInt(UINT data);
    void String(string data);
    void Wstring(wstring data);
    // 이 밖에도 더블 등 자료형이 추가가 되어야 한다면 이 밑으로 추가...

    //// 2진 데이터 관련 함수 (*딱 집어서 하나의 자료형으로 표현할 수가 없는데 그래도 파일 작성을 해야 하는 경우)
    void Byte(void* data, UINT dataSize);

private:
    // 쓰기에 필요한 변수

    //데이터와 표적 파일을 메모리에 담아두기 위한 핸들러(void 포인터:무엇이든 될 수 있는 그거)
    HANDLE file;

    // 파일 작성 중에 미리 확보해야 할 메모리 크기
    // = 파일의 내용의 크기 = 만들려는 파일 크기
    DWORD size = 0;
};

