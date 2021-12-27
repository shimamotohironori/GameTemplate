#pragma once
class DeathCounter:public IGameObject
{
public:
	DeathCounter() {}
	~DeathCounter() {}

	int deathCounter = 0;
};

