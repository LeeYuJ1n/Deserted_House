#pragma once

class Hidden1Scene : public Scene
{
public:
	Hidden1Scene();
	~Hidden1Scene();

	virtual void Update() override;
	virtual void Render() override;

private:
	Hidden1* hidden1;
};

