#include "HighScoreState.h"

#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"
#include "Utility.h"
#include "SceneInfo.h"

using namespace std;


HighScoreState::HighScoreState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{
	m_HighScores = Utility::WriteHighScore(0);
}

void HighScoreState::ProcessInput()
{
	// if true
	int input = _getch();
	if (SceneInfo::GetInstance()->GetSceneName() == SceneInfo::SceneName::HighScore)
	{
		m_pOwner->LoadScene(SceneInfo::SceneName::MainMenu);
	}
}

void HighScoreState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "          - - - HIGH SCORES - - -" << endl << endl;

	for (auto i = m_HighScores.rbegin(); i != m_HighScores.rend(); ++i)
	{
		cout << "             " << *i << endl;
	}

	cout << endl << endl;
	cout << "             Press any key to go back to the main menu" << endl << endl << endl;

}