#pragma once
#include "GameState.h"
#include "Player.h"
#include "Level.h"
#include "SceneInfo.h"

#include <windows.h>
#include <vector>
#include <string>

class StateMachineExampleGame;

class GameplayState : public GameState
{
	StateMachineExampleGame* m_pOwner;
	
	Player m_player;
	Level* m_pLevel;

	bool m_beatLevel;
	int m_skipFrameCount;
	static constexpr int kFramesToSkip = 2;

public:
	GameplayState(StateMachineExampleGame* pOwner);
	~GameplayState();

	virtual void Enter() override;
	virtual void Exit() override;
	virtual bool Update() override;
	virtual void ProcessInput() override;
	virtual void Draw() override;
	virtual SceneInfo::SceneName GetType() override { return SceneInfo::SceneName::Gameplay; };

private:
	void HandleCollision(int newPlayerX, int newPlayerY);
	void UpdateAndCheckCollision();
	bool Load();
	void DrawHUD(const HANDLE& console);
};
