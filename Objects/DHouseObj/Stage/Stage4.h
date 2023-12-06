#pragma once

class Stage4
{
public:
	Stage4();
	~Stage4();

	void Update();
	void Render();

	RectCollider* topPortal_Area;

	Player* player;

private:
	Quad* map;

	std::map < string, Wall* > wallMap;

	// Left Portal
	RectCollider* leftPortal_Area;
	
};

