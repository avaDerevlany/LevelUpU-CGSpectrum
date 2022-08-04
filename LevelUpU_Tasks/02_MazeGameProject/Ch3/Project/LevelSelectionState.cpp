// read all level files, display, and allow user to choose which one to play

#include "LevelSelectionState.h"
#include "GameLevels.h"
#include "SceneInfo.h"

#include <iostream>
#include <string>
#include <conio.h>
#include <stdio.h>

#include "StateMachineExampleGame.h"

using namespace std;

constexpr int kEscapeKey = 27;

LevelSelectionState::LevelSelectionState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{

}

void LevelSelectionState::ProcessInput()
{
	// if true
	int input = _getch();

	if (SceneInfo::GetInstance()->GetSceneName() == SceneInfo::SceneName::LevelSelect)
	{
		if (input == kEscapeKey)
		{
			m_pOwner->LoadScene(SceneInfo::SceneName::MainMenu);
		}
		else
		{
			int numLevels = GameLevels::GetInstance()->GetNumberOfLevels();
			char charInput = (char)input;
			string stringInput = "";
			stringInput += charInput;
			int intInput = stoi(stringInput) - 1;	// +1 added in the menu so levels start at 1 (not 0)

			if (intInput < numLevels && intInput >= 0)
			{
				// boot the level with that input index
				GameLevels::GetInstance()->SetCurrentLevel(intInput);
				m_pOwner->LoadScene(SceneInfo::SceneName::Gameplay);
			}
		}
	}
}

void LevelSelectionState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "          - - - Select a level to play - - -" << endl << endl;

	int numLevels = GameLevels::GetInstance()->GetNumberOfLevels();
	for (int i = 0; i < numLevels; i++)
	{
		cout << "             " << i + 1 << ". Level " << i + 1 << endl;
	}

	cout << endl;
	cout << "       Press ESC to go back to the Main Menu" << endl;
}