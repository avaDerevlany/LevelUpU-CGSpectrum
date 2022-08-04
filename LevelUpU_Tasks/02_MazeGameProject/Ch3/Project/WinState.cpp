#include "WinState.h"

#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"
#include "SceneInfo.h"

using namespace std;


WinState::WinState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{
}

void WinState::ProcessInput()
{
	// if true
	int input = _getch();

	if (SceneInfo::GetInstance()->GetSceneName() == SceneInfo::SceneName::Win)
	{
		m_pOwner->LoadScene(SceneInfo::SceneName::MainMenu);
	}
	
}

void WinState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "          - - - WELL DONE - - -" << endl << endl;
	cout << "             You beat the game!" << endl << endl << endl;
	cout << "             Press any key to go back to the main menu" << endl << endl << endl;
}