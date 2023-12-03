#pragma once

class Hidden1
{
public:
	Hidden1();
	~Hidden1();

	void Update();
	void Render();

	int count;

private:
	Quad* image;
	Quad* image2;
	Quad* image3;
};

