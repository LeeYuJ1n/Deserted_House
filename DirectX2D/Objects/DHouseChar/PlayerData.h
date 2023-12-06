#pragma once

class PlayerData
{
private:
	PlayerData();
	~PlayerData();

	static PlayerData* instance;

public:
	bool objectA = false;
	bool objectB = false;
	bool objectC = false;
	bool objectD = false;
	bool objectE = false;

	static PlayerData* Get()
	{
		if (instance == nullptr)
		{
			instance = new PlayerData();
		}

		return instance;
	}
};

