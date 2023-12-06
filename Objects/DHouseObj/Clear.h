#pragma once

class Clear
{
public:
	Clear();
	~Clear();

	void Update();
	void Render();

private:
	Quad* image;
};

