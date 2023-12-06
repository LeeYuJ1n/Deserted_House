#pragma once

class FirstDHouseScene : public Scene
{
public:
	FirstDHouseScene();
	~FirstDHouseScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	FIrstDHouse* firstdhouse;

	// 아티스트가 "화면 전체:라면 : 씬이 좋고, 그 때는 씬을 상속을 받아야 한다
	// 그렇게 하지 않겠다면 -> 이 헤더 내에서 선언을 해서 만들어두고 -> 처음에는 눈에 안 보이게
	// 숨겨진 벙행 이벤트라면 더욱더 처음부터 만들어두고 -> 그 안에서 image를 보였다가 숨겼다가
};

