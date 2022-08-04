#pragma once
#include "GameState.h"
#include "SceneInfo.h"

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
	virtual void ProcessInput() override;
	virtual void Draw() override;
	virtual SceneInfo::SceneName GetType() override { return SceneInfo::SceneName::LevelSelect; };
};
