#pragma once

class Stage5
{
public:
	Stage5();
	~Stage5();

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

