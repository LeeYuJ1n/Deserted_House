#pragma once

class Stage2Scene : public Scene
{
public:
	Stage2Scene();
	~Stage2Scene();

	virtual void Update() override;
	virtual void Render() override;

private:
	Stage2* stage2;
};

