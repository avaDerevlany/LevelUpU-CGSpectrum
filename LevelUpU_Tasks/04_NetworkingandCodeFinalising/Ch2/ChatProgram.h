#pragma once
#include "ChatServer.h"
#include "ChatClient.h"
#include <string>

class ChatProgram
{
	bool quit = false;
	ChatClient* chatClient = nullptr;
	ChatServer* chatServer = nullptr;
	std::string username = "";

public:
	ChatProgram();
	~ChatProgram();

	void Start();

private:
	int Initialize();
	int ChatMenu();
	std::string AskUserName();
	bool Server();
	bool Client();
	void Quit();

	// Would probably be better to make a parent networking class for the client and server
	// since both share a lot of similarities, however, it works and I am lazy...
	void HandleServerInput();
	void HandleClientInput();
	void DisplayServerChat();
	void DisplayClientChat();

	void EraseLines(int count);	// clears the typed line so that I can add 'You: ' in front of it, looks more like a chat
	void CleanUp();
};