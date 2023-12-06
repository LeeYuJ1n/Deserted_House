#pragma once

class Stage2
{
public:
	Stage2();
	~Stage2();

	void Update();
	void Render();

private:
	Quad* map;
	Quad* objectBLoad;
	Quad* objectELoad;
	Player* player;

	std::map < string, Wall* > wallMap;

	bool ActiveA = false;
	bool ActiveE = false;

	// Right Portal Collider
	RectCollider* rightPortal_Area;

	RectCollider* object1;
	RectCollider* object2;
};

