#pragma once
#include "GameState.h"
#include "SceneInfo.h"

#include <set>

class StateMachineExampleGame;

class HighScoreState : public GameState
{
	StateMachineExampleGame* m_pOwner;
	std::set<int> m_HighScores;

public:
	HighScoreState(StateMachineExampleGame* pOwner);
	~HighScoreState() = default;

	//virtual bool Update() override;
	virtual void ProcessInput() override;
	virtual void Draw() override;
	virtual SceneInfo::SceneName GetType() override { return SceneInfo::SceneName::HighScore; };
};

