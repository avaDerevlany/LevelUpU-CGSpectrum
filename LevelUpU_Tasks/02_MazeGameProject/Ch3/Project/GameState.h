#pragma once

class GameState
{
public:
	virtual ~GameState() {}

	virtual void Enter() {}
	virtual bool Update() { return false; }
	virtual bool ProcessInput() { return false; };
	virtual void Draw() = 0;
	virtual void Exit() {}
};