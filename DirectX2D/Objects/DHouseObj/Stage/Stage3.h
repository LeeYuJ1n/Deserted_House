#pragma once

class Stage3
{
public:
	Stage3();
	~Stage3();

	void Update();
	void Render();

private:
	Quad* map;
	Quad* objectCLoad;
	Quad* objectDLoad;
	Player* player;
	RectCollider* bottomPortal_Area;

	std::map < string, Wall* > wallMap;

	bool ActiveC = false;
	bool ActiveD = false;
	
	// Object Interaction
	RectCollider* object1;
	RectCollider* object2;
};

