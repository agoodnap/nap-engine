#pragma once

class State
{

public:
	State() {}
	~State() {}
	virtual bool init() = 0;
	virtual void exit() = 0;
	virtual void update(const float deltaTime);
};

