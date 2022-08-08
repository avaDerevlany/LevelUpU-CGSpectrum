#pragma once
#include <enet/enet.h>

//Enet setup
int EnetPractice();
void EnetClientServerParctice();
bool SetUpServer(ENetHost* server, ENetAddress address);
bool SetUpClient(ENetHost* client);