#pragma once

class Stage1Scene : public Scene
{
public:
	Stage1Scene();
	~Stage1Scene();

	virtual void Update() override;
	virtual void Render() override;

private:
	Stage1* stage1;
};

