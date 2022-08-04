#include "SettingsState.h"

#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"
#include "AudioManager.h"
#include "SceneInfo.h"

using namespace std;

constexpr int kEscapeKey = 27;
constexpr char kSound = '1';
constexpr char kMainMenu = '2';

SettingsState::SettingsState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{
}

void SettingsState::ProcessInput()
{
	// if true
	int input = _getch();
	if (SceneInfo::GetInstance()->GetSceneName() == SceneInfo::SceneName::Settings)
	{
		if (input == kEscapeKey || (char)input == kMainMenu)
		{
			m_pOwner->LoadScene(SceneInfo::SceneName::MainMenu);
		}
		else if ((char)input == kSound)
		{
			AudioManager::GetInstance()->ToggleSound();
			if (AudioManager::GetInstance()->IsSoundOn())
			{
				AudioManager::GetInstance()->PlayMoneySound();
			}
		}
	}
}

void SettingsState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "          - - - Settings - - -" << endl << endl;
	cout << "             " << kSound << ". Toggle Sound: ";
	if (AudioManager::GetInstance()->IsSoundOn())
	{
		cout << "ON" << endl;
	}
	else
	{
		cout << "OFF" << endl;
	}
	cout << "             " << kMainMenu << ". Back to Main Menu " << endl;
}