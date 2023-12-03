#pragma once

class PlayerWalk : public Action
{
	friend class Player;

public:
	PlayerWalk(Transform* target);
	~PlayerWalk() = default;

	virtual void Update() override;

	void SetPlayer(Player* target);

	Transform* target;

	bool isBlocked = false;

private:
	void Control();
	Player* player;

	float velocity = 0.0f;
	float moveSpeed = 0.5f; // 학원 컴퓨터용
	// float moveSpeed = 1.0f; // 노트북용
	
};

