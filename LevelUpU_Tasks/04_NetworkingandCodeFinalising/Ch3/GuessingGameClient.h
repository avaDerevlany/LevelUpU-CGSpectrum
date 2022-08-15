#pragma once
#include <enet/enet.h>
#include "GuessingGamePeer.h"

class GuessingGameClient : public GuessingGamePeer
{
    ENetPeer* server = nullptr;


public:
    GuessingGameClient();
    ~GuessingGameClient();

    ENetPeer* GetServer() { return server; };

    Info ConnectToServer(enet_uint32 addrHost = ENET_HOST_ANY, enet_uint16 addrPort = 1234);
    Info HandleEvent() override;
    Info StringEvent(ENetEvent* event, Packet::PacketHeaderType type);
    Info BoolEvent(ENetEvent* event);
    //Info SendPacket(Packet packetInfo);
    void CloseConnection() override;
};