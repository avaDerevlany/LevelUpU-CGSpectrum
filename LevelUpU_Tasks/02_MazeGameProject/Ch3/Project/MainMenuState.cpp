#include "MainMenuState.h"
#include "SceneInfo.h"

#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"

using namespace std;

constexpr int kEscapeKey = 27;

constexpr char kPlay = '1';
constexpr char kLevelSelect = '2';
constexpr char kHighScore = '3';
constexpr char kSettings = '4';
constexpr char kQuit = '5';

MainMenuState::MainMenuState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{
	m_shouldQuit = false;
}

bool MainMenuState::Update()
{
	return m_shouldQuit;
}

void MainMenuState::ProcessInput()
{
	//bool shouldQuit = false;
	// if tue
	int input = _getch();

	if (SceneInfo::GetInstance()->GetSceneName() == SceneInfo::SceneName::MainMenu)
	{
		if (input == kEscapeKey || (char)input == kQuit)
		{
			m_shouldQuit = true;
		}
		else if ((char)input == kPlay)
		{
			m_pOwner->LoadScene(SceneInfo::SceneName::Gameplay);
		}
		else if ((char)input == kLevelSelect)
		{
			m_pOwner->LoadScene(SceneInfo::SceneName::LevelSelect);
		}
		else if ((char)input == kHighScore)
		{
			m_pOwner->LoadScene(SceneInfo::SceneName::HighScore);
		}
		else if ((char)input == kSettings)
		{
			m_pOwner->LoadScene(SceneInfo::SceneName::Settings);
		}
	}
	//return shouldQuit;
}

void MainMenuState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "          - - - MAIN MENU - - -" << endl << endl;
	cout << "             " << kPlay << ". Play " << endl;
	cout << "             " << kLevelSelect << ". Select level " << endl;
	cout << "             " << kHighScore << ". High Score " << endl;
	cout << "             " << kSettings << ". Settings " << endl;
	cout << "             " << kQuit << ". Quit " << endl;
}