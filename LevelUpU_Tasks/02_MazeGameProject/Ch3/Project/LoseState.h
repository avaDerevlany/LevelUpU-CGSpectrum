#pragma once
#include "GameState.h"
#include "SceneInfo.h"

class StateMachineExampleGame;

class LoseState : public GameState
{
	StateMachineExampleGame* m_pOwner;

public:
	LoseState(StateMachineExampleGame* pOwner);
	~LoseState() = default;

	//virtual bool Update(bool processInput = true) override;
	virtual void ProcessInput() override;
	virtual void Draw() override;
	virtual SceneInfo::SceneName GetType() override { return SceneInfo::SceneName::Lose; };
};


