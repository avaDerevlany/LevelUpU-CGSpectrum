#include "Game.h"

Game::Game()
	: m_pStateMachine(nullptr)
{

}

void Game::Initialize(GameStateMachine* pStateMachine)
{
	if (pStateMachine != nullptr)
	{
		pStateMachine->Init();
		m_pStateMachine = pStateMachine;
	}
}

/* 
	Seperated the original Update function into a game update function and a game Process Input function
	Originally the Update function was handling two completely different tasks, updating the game
	and handling the input, the two tasks separated by a if/else statement.
	I separated them because each function should try to do only one thing,
	as well as, that way, later on down the line, if the we were to run the Update function and the
	Process Input function in different threads, the game could update continuously and not get
	blocked by the input gathering.
	Doing this however, required editing a lot of the files. All files that inherit from Game and
	all files that inherit from GameState.
	Until threading is implemented, separating the two does require an extra input to register when
	the game has ended and a new scene is loaded.
*/
void Game::RunGameLoop()
{
	bool isGameOver = false;

	while (!isGameOver)
	{
		// Update
		isGameOver = Update();
		// Draw
		Draw();
		// process input
		ProcessInput();
	}

	Draw();
}

void Game::Deinitialize()
{
	if (m_pStateMachine != nullptr)
		m_pStateMachine->Cleanup();
}

bool Game::Update()
{
	return m_pStateMachine->UpdateCurrentState();
}

void Game::ProcessInput()
{
	m_pStateMachine->ProcessInputCurrentState();
}

void Game::Draw()
{
	m_pStateMachine->DrawCurrentState();
}
