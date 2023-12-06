#pragma once

class PlayerDead : public Action
{
public:
	PlayerDead(Transform* target);
	~PlayerDead() = default;

	virtual void Update() override;

private:
	void Control();

	Transform* target;
	float velocity = 0.0f;
};

