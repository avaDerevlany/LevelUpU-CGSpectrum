#pragma once
#include "GameState.h"
#include "SceneInfo.h"

class StateMachineExampleGame;

class MainMenuState : public GameState
{
	StateMachineExampleGame* m_pOwner;

	bool m_shouldQuit;

public:
	MainMenuState(StateMachineExampleGame* pOwner);
	~MainMenuState() = default;

	virtual bool Update() override;
	virtual void ProcessInput() override;
	virtual void Draw() override;
	virtual SceneInfo::SceneName GetType() override { return SceneInfo::SceneName::MainMenu; };
};

