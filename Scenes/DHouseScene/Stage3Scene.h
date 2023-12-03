#pragma once

class Stage3Scene : public Scene
{
public:
	Stage3Scene();
	~Stage3Scene();

	virtual void Update() override;
	virtual void Render() override;

private:
	Stage3* stage3;
};

