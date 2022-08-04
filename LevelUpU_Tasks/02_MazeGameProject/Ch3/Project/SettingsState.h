#pragma once
#include "GameState.h"
#include "SceneInfo.h"

class StateMachineExampleGame;

class SettingsState : public GameState
{
	StateMachineExampleGame* m_pOwner;

public:
	SettingsState(StateMachineExampleGame* pOwner);
	~SettingsState() = default;

	//virtual bool Update(bool processInput = true) override;
	virtual void ProcessInput() override;
	virtual void Draw() override;
	virtual SceneInfo::SceneName GetType() override { return SceneInfo::SceneName::Settings; };
};
