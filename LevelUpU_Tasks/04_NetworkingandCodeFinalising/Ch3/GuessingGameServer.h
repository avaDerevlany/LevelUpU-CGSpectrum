#pragma once
#include <enet/enet.h>
#include <map>
#include "GuessingGamePeer.h"

class GuessingGameServer : public GuessingGamePeer
{
	ENetAddress address;
	int numberToGuess;
	bool gameWon;

	std::map<int, std::string> peerNames;

public:
	GuessingGameServer(enet_uint32 addrHost = ENET_HOST_ANY, enet_uint16 addrPort = 1234);
	~GuessingGameServer();

	ENetAddress GetAddress() { return address; };

	Info HandleEvent() override;
	//Info SendPacket(Packet packetInfo) override;
	//Info SendPacket_ToAll(Packet packetInfo);
	Info SendAllOtherClients_ClientUpdate(ENetEvent* event);
	void CloseConnection() override;

private:
	void ChooseRandomNumber();
	Info GuessEvent(ENetEvent* event);
	Info StringEvent(ENetEvent* event);
	Info ConnectionEvent(ENetEvent* event);
	Info DisconnectEvent(ENetEvent* event);
};