#include "ChatServer.h"
#include "ChatClient.h"
#include "ChatProgram.h"
#include <string>
#include <iostream>
#include <thread>

using namespace std;

ChatProgram::ChatProgram()
{
	Initialize();
}

ChatProgram::~ChatProgram()
{
	CleanUp();
	atexit(enet_deinitialize);
}

int ChatProgram::Initialize()
{
	if (enet_initialize() != 0)
	{
		cout << "An error occurred while initializing ENet.\n" << endl;
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}

void ChatProgram::Start()
{
	bool successfulChat = false;
	do
	{
		system("cls");
		int userInput = ChatMenu();

		switch (userInput)
		{
		case 1:
			// set up server
			username = AskUserName();
			system("cls");
			cout << "---Enter \'quit\' at any time to end the chat---\n" << endl;
			successfulChat = Server();
			break;
		case 2:
			// set up client
			username = AskUserName();
			system("cls");
			cout << "---Enter \'quit\' at any time to end the chat---\n" << endl;
			successfulChat = Client();
			break;
		case 3:
			// quit
			Quit();
			successfulChat = true;
			break;
		default:
			// invalid input
			cout << "An error has occured, please restart" << endl;
			successfulChat = false;
			break;
		}
	} while (!successfulChat);
}

int ChatProgram::ChatMenu()
{
	cout << "Welcome to \"Rudimentary Chat Program\"" << endl;
	cout << "---------------------------------------" << endl;
	cout << "What would you like to do?" << endl;
	cout << "   1) Set up a new chat" << endl;
	cout << "   2) Join a chat" << endl;
	cout << "   3) Quit\n" << endl;

	string userInput;
	bool waitForInput = true;

	while (waitForInput)
	{
		//cin >> userInput;
		getline(cin, userInput);

		//if (userInput > 0 && userInput < 4) waitForInput = false;
		if (userInput == "1" || userInput == "2" || userInput == "3") waitForInput = false;
	}

	return stoi(userInput);
}

string ChatProgram::AskUserName()
{
	cout << "Please enter your name: ";
	string userName;
	getline(cin, userName);
	cout << endl;
	return userName;
}

bool ChatProgram::Server()
{
	chatServer = new ChatServer();
	bool successfullyCreated = (chatServer->GetServer() != nullptr);

	// server created
	if (successfullyCreated)
	{
		cout << "Server online\n" << endl;

		thread displayChatThread(&ChatProgram::DisplayServerChat, this);	// bound version of the thread
		thread handleInputThread(&ChatProgram::HandleServerInput, this);

		while (!quit) {}

		displayChatThread.join();
		handleInputThread.join();
		chatServer->CloseServer();
	}
	else
	{
		string pauseScreen;
		getline(cin, pauseScreen);
	}

	CleanUp();

	return successfullyCreated;
}

bool ChatProgram::Client()
{
	chatClient = new ChatClient();
	bool successfullyConnected = chatClient->ConnectToChatServer();

	if (successfullyConnected)
	{
		thread displayChatThread(&ChatProgram::DisplayClientChat, this);
		thread handleInputThread(&ChatProgram::HandleClientInput, this);

		while (!quit) {}

		displayChatThread.join();
		handleInputThread.join();
		chatClient->CloseClient();
	}
	else
	{
		string pauseScreen;
		getline(cin, pauseScreen);
	}

	CleanUp();

	return successfullyConnected;
}

void ChatProgram::Quit()
{
	cout << "Goodbye\n" << endl;
}

void ChatProgram::HandleServerInput()
{
	string msg;

	while (!quit)
	{
		//cout << "You: ";
		getline(cin, msg);

		if (msg == "quit") quit = true;
		else
		{
			string chatMsg = username + ": " + msg;
			chatServer->SendStringPacket_ToAll(chatMsg);

			EraseLines(2);
			cout << "You: " << msg << endl;
		}
	}
}

void ChatProgram::HandleClientInput()
{
	string msg;

	while (!quit)
	{
		//cout << "You: ";
		getline(cin, msg);

		if (msg == "quit") quit = true;
		else
		{
			string chatMsg = username + ": " + msg;
			chatClient->SendStringPacket(chatMsg);

			EraseLines(2);
			cout << "You: " << msg << endl;
		}
	}
}

void ChatProgram::DisplayServerChat()
{
	while (!quit)
	{
		chatServer->HandleEvent();
	}
}

void ChatProgram::DisplayClientChat()
{
	while (!quit)
	{
		chatClient->HandleEvent();
	}
}

void ChatProgram::EraseLines(int count)
{
	if (count > 0)
	{
		std::cout << "\x1b[2K"; // Delete current line
		// i=1 because we included the first line
		for (int i = 1; i < count; i++)
		{
			std::cout
				<< "\x1b[1A" // Move cursor up one
				<< "\x1b[2K"; // Delete the entire line
		}
		std::cout << "\r"; // Resume the cursor at beginning of line
	}
}

void ChatProgram::CleanUp()
{
	if (chatServer != nullptr)
	{
		delete chatServer;
		chatServer = nullptr;
	}
	if (chatClient != nullptr)
	{
		delete chatClient;
		chatClient = nullptr;
	}
}