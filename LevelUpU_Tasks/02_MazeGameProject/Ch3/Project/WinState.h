#pragma once
#include "GameState.h"
#include "SceneInfo.h"

class StateMachineExampleGame;

class WinState : public GameState
{
	StateMachineExampleGame* m_pOwner;

public:
	WinState(StateMachineExampleGame* pOwner);
	~WinState() = default;

	//virtual bool Update(bool processInput = true) override;
	virtual void ProcessInput() override;
	virtual void Draw() override;
	virtual SceneInfo::SceneName GetType() override { return SceneInfo::SceneName::Win; };
};
