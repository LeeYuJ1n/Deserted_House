#pragma once

class Stage4Scene : public Scene
{
public:
	Stage4Scene();
	~Stage4Scene();

	virtual void Update() override;
	virtual void Render() override;

private:
	Stage4* stage4;
};

