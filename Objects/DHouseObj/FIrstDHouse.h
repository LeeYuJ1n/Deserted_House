#pragma once

class Stage1;
class Stage2;
class Hidden1;

class FIrstDHouse
{
public:
	FIrstDHouse();
	~FIrstDHouse();

	void Update();
	void Render();

private:
	Quad* background;   // 백그라운드 이미지
	Button* esterEgg_Btn; // 도화가 사진 이스터에그 버튼
	Button* start_Btn;    // 게임 시작을 위한 버튼
	// Button* option_Btn;   // 게임 옵션 버튼
	Stage1* stage1;
	Stage2* stage2;
	Hidden1* hidden1;
};

