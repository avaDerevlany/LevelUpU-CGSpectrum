#pragma once
#include <enet/enet.h>
#include <iostream>
#include "../Section4Header.h"

class ChatServer
{
	ENetHost* server = nullptr;
	ENetAddress address;

public:
	ChatServer(enet_uint32 host = ENET_HOST_ANY, enet_uint16 port = 1234);
	~ChatServer();
	
	ENetAddress GetAddress() { return address; };
	ENetHost* GetServer() { return server; };

	void HandleEvent();
	void SendStringPacket(std::string msg, ENetPeer* client);
	void SendPremadeDataPacket(enet_uint8* data, size_t dataSize, ENetPeer* client);
	void SendStringPacket_ToAll(std::string msg);
	void SendAllOtherClients_ClientUpdate(ENetEvent* event);
	void SendAllOtherClients_ClientUpdate(ENetEvent* event, std::string msg);
	void CloseServer();
};
