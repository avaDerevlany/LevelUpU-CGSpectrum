#pragma once
#include <enet/enet.h>
#include "PacketStructs.h"

struct Info
{
    enum MessageType
    {
        GameInfo,
        PlayerMsg,
        Status,
        Debug,
        NoUpdate
    };

    MessageType type;
    bool success;
    std::string msg;
    bool gameOver;
    // display or not?

    Info(MessageType type = MessageType::NoUpdate, bool success = false, std::string msg = "", bool gameOver = false)
        : type(type), success(success), msg(msg), gameOver(gameOver)
    {

    }
};

class GuessingGamePeer
{
public:
    enum ConnectionType
    {
        Invalid,
        Server,
        Client
    };

protected:
	ENetHost* host = nullptr;
    ConnectionType type = Invalid;

public:
    GuessingGamePeer() {};
    ~GuessingGamePeer() { CloseConnection(); };
    //Info Initialize();

    ENetHost* GetHost() { return host; };
    ConnectionType GetType() { return type; };

    virtual Info HandleEvent() = 0;
    Info SendPacket(Packet* packetInfo, ENetPeer* peer);
    Info SendPacket_ToAll(Packet* packetInfo);
    Info SendEventData(enet_uint8* data, size_t dataSize, ENetPeer* peer);
    virtual void CloseConnection();
};