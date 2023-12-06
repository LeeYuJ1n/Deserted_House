#pragma once

class Stage5Scene : public Scene
{
public:
	Stage5Scene();
	~Stage5Scene();

	virtual void Update() override;
	virtual void Render() override;

private:
	Stage5* stage5;
};

