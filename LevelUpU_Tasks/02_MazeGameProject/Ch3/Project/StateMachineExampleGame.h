#pragma once
#include "GameStateMachine.h"
#include "SceneInfo.h"

class Game;
class GameState;

class StateMachineExampleGame : public GameStateMachine
{
//public:
//	

private:
	Game* m_pOwner;

	GameState* m_pCurrentState;
	GameState* m_pNextState;

public:
	StateMachineExampleGame(Game* pOwner);

	virtual bool Init() override;
	virtual bool UpdateCurrentState() override;
	virtual void ProcessInputCurrentState() override;
	virtual void DrawCurrentState() override;
	virtual void ChangeState(GameState* pNewState) override;
	void LoadScene(SceneInfo::SceneName scene);
	SceneInfo::SceneName GetCurrentState();
	virtual bool Cleanup() override;
};

