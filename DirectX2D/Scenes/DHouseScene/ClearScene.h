#pragma once

class ClearScene : public Scene
{
public:
	ClearScene();
	~ClearScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	Clear* clear;
};

