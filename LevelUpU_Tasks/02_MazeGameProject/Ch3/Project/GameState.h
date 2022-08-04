#pragma once
#include "StateMachineExampleGame.h"
#include "SceneInfo.h"

class GameState
{
protected:
	bool isActive = false;

public:
	virtual ~GameState() {};

	virtual void Enter() { isActive = true; };
	virtual bool Update() { return false; };
	virtual void ProcessInput() { };
	virtual void Draw() = 0;
	virtual void Exit() { isActive = false; };
	virtual SceneInfo::SceneName GetType() { return SceneInfo::SceneName::None; };

	virtual bool IsSceneActive() { return isActive; };
};