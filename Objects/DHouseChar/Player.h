#pragma once

class Player : public GameObject
{
private:
	enum ActionType
	{
		IDLE, WALK, DEAD
	};

public:
	Player();
	~Player();

	void Update();
	void Render();

	static bool GetObjectA() { return objectA; }
	static bool GetObjectB() { return objectB; }
	static bool GetObjectC() { return objectC; }
	static bool GetObjectD() { return objectD; }
	static bool GetObjectE() { return objectE; }

	RectCollider* characterArea;

	void AddBlockObject(RectCollider* coll);

private:
	void Control();
	void Move();
	void SetIdle();
	void SetAction(int type);
	void CreateActions();
	void BlockObject(vector<RectCollider*> collList);

	vector<RectCollider*> BlockList;
	
	static bool objectA;
	static bool objectB;
	static bool objectC;
	static bool objectD;
	static bool objectE;

	map<ActionType, Action*> actions;

	ActionType curAction = IDLE;

	// Texture* sLayer;

	IntValueBuffer* intValueBuffer;
	FloatValueBuffer* floatValueBuffer;
};

