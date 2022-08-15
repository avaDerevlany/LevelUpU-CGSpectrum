#include "GuessingGameServer.h"
#include "GuessingGameClient.h"
#include "GuessingGameProgram.h"
#include <string>
#include <iostream>
#include <thread>

using namespace std;

GuessingGameProgram::GuessingGameProgram()
{
	Initialize();
}

GuessingGameProgram::~GuessingGameProgram()
{
	CleanUp();
	atexit(enet_deinitialize);
}

Info GuessingGameProgram::Initialize()
{
	if (enet_initialize() != 0)
	{
		return Info(Info::MessageType::Status, false, "An error occurred while initializing ENet.");
	}

	return Info(Info::MessageType::Status, true, "Successfuly initialized ENet.");
}

void GuessingGameProgram::Start()
{
	bool successfulGame = false;
	string username;
	do
	{
		system("cls");
		int userInput = Menu();

		switch (userInput)
		{
		case 1:
			// set up server
			//username = AskUserName();
			system("cls");
			cout << "---Enter \'quit\' at any time to close the server---\n" << endl;
			if (Server())
			{
				successfulGame = RunGame();
			}
			break;
		case 2:
			// set up client
			username = AskUserName();
			system("cls");
			cout << "-----Enter \'quit\' at any time to leave----" << endl;
			cout << "Try to guess the number! (between 0 and 100)\n" << endl;
			if (Client(username))
			{
				successfulGame = RunGame();
			}
			break;
		case 3:
			// quit
			Quit();
			successfulGame = true;
			break;
		default:
			// invalid input
			cout << "An error has occured, please restart" << endl;
			successfulGame = false;
			break;
		}
	} while (!successfulGame);
}

int GuessingGameProgram::Menu()
{
	cout << "Would you like to play a number guessing game?" << endl;
	cout << "----------------------------------------------" << endl;
	//cout << "What would you like to do?" << endl;
	cout << "   1) Set up a new game" << endl;
	cout << "   2) Join a game" << endl;
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

string GuessingGameProgram::AskUserName()
{
	cout << "Please enter your name: ";
	string userName;
	getline(cin, userName);
	cout << endl;
	return userName;
}

bool GuessingGameProgram::Server()
{
	peer = new GuessingGameServer();
	bool successfullyCreated = (peer->GetHost() != nullptr);

	if (successfullyCreated)
	{
		cout << "Server online\n" << endl;
	}
	else
	{
		string pauseScreen;
		getline(cin, pauseScreen);
	}

	//// server created
	//if (successfullyCreated)
	//{
	//	cout << "Server online\n" << endl;

	//	thread displayChatThread(&ChatProgram::DisplayServerChat, this);	// bound version of the thread
	//	thread handleInputThread(&ChatProgram::HandleServerInput, this);

	//	while (!quit) {}

	//	displayChatThread.join();
	//	handleInputThread.join();
	//	chatServer->CloseServer();
	//}
	//else
	//{
	//	string pauseScreen;
	//	getline(cin, pauseScreen);
	//}

	//CleanUp();

	return successfullyCreated;
}

bool GuessingGameProgram::Client(std::string username)
{
	peer = new GuessingGameClient();
	Info successfullyConnected = ((GuessingGameClient*)peer)->ConnectToServer();

	PrintInfo(successfullyConnected);

	if (successfullyConnected.success)
	{
		StringPacket connectionPacket = StringPacket(username, Packet::PacketHeaderType::Connection);
		do
		{
			successfullyConnected = peer->SendPacket(&connectionPacket, ((GuessingGameClient*)peer)->GetServer());
		} while (!successfullyConnected.success);
		
	}
	else
	{
		string pauseScreen;
		getline(cin, pauseScreen);
	}

	return successfullyConnected.success;
}

bool GuessingGameProgram::RunGame()
{
	thread displayGameThread(&GuessingGameProgram::DisplayGame, this);	// bound version of the thread
	thread handleInputThread(&GuessingGameProgram::HandleInput, this);

	while (!quit) {}

	displayGameThread.join();
	handleInputThread.join();
	peer->CloseConnection();

	CleanUp();

	return true;
}

void GuessingGameProgram::Quit()
{
	cout << "Goodbye\n" << endl;
}

void GuessingGameProgram::HandleInput()
{
	string msg;

	while (!quit)
	{
		getline(cin, msg);

		if (!quit && msg == "quit") quit = true;
		else if (!quit)
		{
			EraseLines(2);

			if (peer->GetType() == GuessingGamePeer::ConnectionType::Server)
			{
				cout << "Server: " << msg << endl;
			}

			// if the input is a number
			if (isNumber(msg))
			{
				HandleNumberInput(stoi(msg));
			}

			// else the input is a string
			else
			{
				HandleStringInput(msg);
			}
		}
	}
}

void GuessingGameProgram::HandleNumberInput(int numberGuess)
{
	Info successInfo = Info();

	GuessingPacket guessingPacket = GuessingPacket(numberGuess);

	// only the clients should be sending
	if (peer->GetType() == GuessingGamePeer::ConnectionType::Client)
	{
		successInfo = peer->SendPacket(&guessingPacket, ((GuessingGameClient*)peer)->GetServer());
	}
	else
	{
		successInfo.success = false;
		successInfo.msg = "Server tried to guess, it should not be doing that, it knows the answer.";
	}
	PrintInfo(successInfo);
}

void GuessingGameProgram::HandleStringInput(string msg)
{
	Info successInfo = Info();

	StringPacket stringPacket = StringPacket(msg, Packet::PacketHeaderType::ServerMsg);

	if (peer->GetType() == GuessingGamePeer::ConnectionType::Server)
	{
		successInfo = peer->SendPacket_ToAll(&stringPacket);
	}
	else if (peer->GetType() == GuessingGamePeer::ConnectionType::Client)
	{
		stringPacket.type = Packet::PacketHeaderType::ClientMsg;
		successInfo = peer->SendPacket(&stringPacket, ((GuessingGameClient*)peer)->GetServer());
	}

	PrintInfo(successInfo);
}

void GuessingGameProgram::DisplayGame()
{
	Info gameInfo = Info();
	while (!quit)
	{
		gameInfo = peer->HandleEvent();
		PrintInfo(gameInfo);

		if (gameInfo.gameOver)
		{
			quit = true;
		}
	}
}

void GuessingGameProgram::PrintInfo(Info info)
{
	if (info.type == Info::MessageType::GameInfo)
	{
		cout << "GAME: " << info.msg << endl << endl;
	}
	if (info.type == Info::MessageType::PlayerMsg)
	{
		cout << info.msg << endl << endl;
	}
	else if (info.type == Info::MessageType::Status)
	{
		cout << "STATUS: " << info.msg << endl << endl;
	}
	else if (debug && info.type == Info::MessageType::Debug)
	{
		cout << "DEBUG: " << info.msg << endl << endl;
	}
}

void GuessingGameProgram::EraseLines(int count)
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

void GuessingGameProgram::CleanUp()
{
	if (peer != nullptr)
	{
		delete peer;
		peer = nullptr;
	}
}

bool GuessingGameProgram::isNumber(const string& s)
{
	for (char const& ch : s)
	{
		if (std::isdigit(ch) == 0)
			return false;
	}
	return true;
}