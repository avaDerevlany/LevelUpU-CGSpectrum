#pragma once
#include <enet/enet.h>
#include <iostream>
#include "../Section4Header.h"

class ChatClient
{
    ENetHost* client = nullptr;
    ENetPeer* server = nullptr;


public:
    ChatClient();
    ~ChatClient();

    ENetHost* GetClient() { return client; };

    bool ConnectToChatServer(enet_uint32 host = ENET_HOST_ANY, enet_uint16 port = 1234);
    void HandleEvent();
    void SendStringPacket(std::string msg);
    void CloseClient();
};