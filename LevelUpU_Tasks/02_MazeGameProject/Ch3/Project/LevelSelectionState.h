#pragma once
#include "GameState.h"

#include <vector>
#include <string>

class StateMachineExampleGame;

class LevelSelectionState : public GameState
{
	StateMachineExampleGame* m_pOwner;

public:
	LevelSelectionState(StateMachineExampleGame* pOwner);
	~LevelSelectionState() = default;

	//virtual bool Update() override;
	virtual bool ProcessInput() override;
	virtual void Draw() override;
};
