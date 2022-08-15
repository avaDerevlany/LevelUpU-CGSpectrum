#pragma once
#include "GuessingGameServer.h"
#include "GuessingGameClient.h"
#include <string>

class GuessingGameProgram
{
	bool quit = false;
	GuessingGamePeer* peer;
	
	bool debug = false;

public:
	GuessingGameProgram();
	~GuessingGameProgram();

	void Start();

private:
	Info Initialize();
	int Menu();
	std::string AskUserName();
	bool Server();
	bool Client(std::string username);
	bool RunGame();
	void Quit();

	void HandleInput();
	void DisplayGame();

	void HandleNumberInput(int numberGuess);
	void HandleStringInput(std::string msg);

	void PrintInfo(Info info);
	void CleanUp();

	void EraseLines(int count);	// clears the typed line so that I can add 'You: ' in front of it, looks more like a chat
	bool isNumber(const std::string& s);
};