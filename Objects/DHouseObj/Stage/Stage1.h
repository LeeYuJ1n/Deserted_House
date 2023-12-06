#pragma once
#include "Framework.h"

class Stage2;
class Stage4;
class Stage5;

class Stage1
{
public:
	Stage1();
	~Stage1();

	// bool objectA = PLAYERDATA->objectA = true;

	static Stage1* instance;

	void Update();
	void Render();

	bool object;

	// Left Portal Collider
	RectCollider* leftPortal_Area;

	// Top Portal Collider
	RectCollider* topPortal_Area;

	// Right Portal Collider
	RectCollider* rightPortal_Area;

	// Bottom Portal Collider
	RectCollider* bottomPortal_Area;

	// Left Top Collider
	RectCollider* leftTop_Collider;
	RectCollider* leftTopSide_Collider;

	// Left Bottom Collider
	RectCollider* leftBotton_Collider;
	RectCollider* leftBottomSide_Collider;

	// RIght Top Collider
	RectCollider* rightTop_Collider;
	RectCollider* rightTopSide_Collider;

	// Right Bottom Collider
	RectCollider* rightBottom_Collider;
	RectCollider* rightBottomSide_Collider;

	

private:
	Quad* map;
	Quad* objectALoad;
	Quad* noExit;
	Player* player;
	Stage2* stage2;
	Stage4* stage4;
	Stage5* stage5;

	Quad* resultObject1;
	Quad* resultObject2;
	Quad* resultObject3;
	Quad* resultObject4;
	Quad* resultObject5;

	Quad* noObject1;
	Quad* noObject2;
	Quad* noObject3;
	Quad* noObject4;
	Quad* noObject5;

	std::map < string, Wall* > wallMap;
	
	bool Active = false;
	bool Active2 = false;
	bool playerPos = false;

	// Objects
	RectCollider* object1;
};
