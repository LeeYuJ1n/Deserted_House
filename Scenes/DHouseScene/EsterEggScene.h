#pragma once

class EsterEggScene : public Scene
{
public:
	EsterEggScene();
	~EsterEggScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	EsterEgg* esterEgg;
};

