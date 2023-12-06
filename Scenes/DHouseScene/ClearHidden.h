#pragma once

class ClearHidden : public Scene
{
public:
	ClearHidden();
	~ClearHidden();

	virtual void Update() override;
	virtual void Render() override;

private:
	Quad* image;
};

