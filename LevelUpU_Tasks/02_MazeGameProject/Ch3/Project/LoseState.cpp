#include "LoseState.h"
#include "SceneInfo.h"

#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"

using namespace std;


LoseState::LoseState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{
}

void LoseState::ProcessInput()
{
	// if true
	int input = _getch();

	if (SceneInfo::GetInstance()->GetSceneName() == SceneInfo::SceneName::Lose)
	{
		m_pOwner->LoadScene(SceneInfo::SceneName::MainMenu);
	}
	
}

void LoseState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "          - - - GAME OVER - - -" << endl << endl;
	cout << "             Better luck next time." << endl << endl << endl;
	cout << "             Press any key to go back to the main menu" << endl << endl << endl;
}