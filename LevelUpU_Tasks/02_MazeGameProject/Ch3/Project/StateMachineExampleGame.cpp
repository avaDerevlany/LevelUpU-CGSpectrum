#include "StateMachineExampleGame.h"
#include "LevelSelectionState.h"
#include "GameplayState.h"
#include "MainMenuState.h"
#include "SettingsState.h"
#include "HighScoreState.h"
#include "LoseState.h"
#include "WinState.h"
#include "Game.h"

//StateMachineExampleGame::SceneName currentSceneState = StateMachineExampleGame::SceneName::None;


StateMachineExampleGame::StateMachineExampleGame(Game* pOwner)
	: m_pOwner(pOwner)
	, m_pCurrentState(nullptr)
	, m_pNextState(nullptr)
{
}

bool StateMachineExampleGame::Init()
{
	LoadScene(SceneInfo::SceneName::MainMenu);
	return true;
}

bool StateMachineExampleGame::UpdateCurrentState()
{
	bool done = false;
	if (m_pNextState != nullptr)
	{
		ChangeState(m_pNextState);
		m_pNextState = nullptr;
	}

	if (m_pCurrentState != nullptr)
	{
		//if (processInput) m_pCurrentState->ProcessInput();
		done = m_pCurrentState->Update();
	}
	return done;
}

void StateMachineExampleGame::ProcessInputCurrentState()
{
	m_pCurrentState->ProcessInput();
}

void StateMachineExampleGame::DrawCurrentState()
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Draw();
	}
}

void StateMachineExampleGame::ChangeState(GameState* pNewState)
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Exit();
	}

	delete m_pCurrentState;
	m_pCurrentState = pNewState;
	SceneInfo::GetInstance()->SetCurrentScene(m_pCurrentState->GetType());
	pNewState->Enter();
}

void StateMachineExampleGame::LoadScene(SceneInfo::SceneName scene)
{
	switch (scene)
	{
	case SceneInfo::SceneName::None:
		// do nothing
		break;
	case SceneInfo::SceneName::MainMenu:
		m_pNextState = new MainMenuState(this);
		//SceneInfo::GetInstance()->SetCurrentScene(SceneInfo::SceneName::MainMenu);
		break;
	case SceneInfo::SceneName::LevelSelect:
		m_pNextState = new LevelSelectionState(this);
		//SceneInfo::GetInstance()->SetCurrentScene(SceneInfo::SceneName::LevelSelect);
		break;
	case SceneInfo::SceneName::Gameplay:
		m_pNextState = new GameplayState(this);
		//SceneInfo::GetInstance()->SetCurrentScene(SceneInfo::SceneName::Gameplay);
		break;
	case SceneInfo::SceneName::Settings:
		m_pNextState = new SettingsState(this);
		//SceneInfo::GetInstance()->SetCurrentScene(SceneInfo::SceneName::Settings);
		break;
	case SceneInfo::SceneName::HighScore:
		m_pNextState = new HighScoreState(this);
		//SceneInfo::currentScene = SceneInfo::SceneName::HighScore;
		break;
	case SceneInfo::SceneName::Win:
		m_pNextState = new WinState(this);
		//SceneInfo::currentScene = SceneInfo::SceneName::Win;
		break;
	case SceneInfo::SceneName::Lose:
		m_pNextState = new LoseState(this);
		//SceneInfo::currentScene = SceneInfo::SceneName::Lose;
		break;
	}

}

SceneInfo::SceneName StateMachineExampleGame::GetCurrentState()
{
	return m_pCurrentState->GetType();
}

bool StateMachineExampleGame::Cleanup()
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Exit();
		delete m_pCurrentState;
	}

	return true;
}
