#pragma once
#include <enet/enet.h>

//Ch 1 / Ch 2
int EnetPractice();
void EnetClientServerPractice();
ENetHost* SetUpServer(ENetHost* server, ENetAddress address);
ENetHost* SetUpClient(ENetHost* client);
ENetPeer* HandleEvent(ENetHost* client);
ENetPeer* ConnectToServer(ENetHost* client, ENetAddress address);
void SendPacket(ENetPeer* client, ENetHost* host);
