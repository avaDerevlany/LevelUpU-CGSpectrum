#pragma once
#include <string>

struct Packet
{
    enum PacketHeaderType
    {
        Invalid,
        Guess,
        ServerMsg,
        ClientMsg,
        Connection,
        GameOver
    };

    PacketHeaderType type = Invalid;

    Packet() {};

    PacketHeaderType GetType() { return type; };

    virtual size_t SizeOf() const
    { 
        return sizeof(type);
    };

    static void serialize(const Packet& packet, char* data)
    {
        size_t bufferIdx = 0;
        size_t typeSize = sizeof(packet.type);
        memcpy(&data[bufferIdx], &packet.type, typeSize);
    };

    static void deserialize(char* data, size_t dataLength, Packet& packet)
    {
        memcpy(&packet.type, &data[0], sizeof(packet.type));
    };
};

struct GuessingPacket : public Packet
{
    //std::string peerName; // peer ID is already sent with the message
    int guess;
    //bool won;

    GuessingPacket(int guess)
        : guess(guess)
    {
        type = Guess;
    }

    size_t SizeOf() const override
    {
        size_t size = sizeof(type);
        size += sizeof(guess);
        return size;
    }

    static void serialize(const GuessingPacket& packet, char* data)
    {
        size_t bufferIdx = 0;
        size_t typeSize = sizeof(packet.type);
        memcpy(&data[bufferIdx], &packet.type, typeSize);

        // Serialize message
        bufferIdx += typeSize;
        size_t intSize = sizeof(packet.guess);
        memcpy(&data[bufferIdx], &packet.guess, intSize);
    };

    static void deserialize(char* data, size_t dataLength, GuessingPacket& packet)
    {
        memcpy(&packet.type, &data[0], sizeof(packet.type));
        memcpy(&packet.guess, &data[sizeof(packet.type)], sizeof(packet.guess));
    };
};

// higher, lower, correct as enum (int) instead of string?

struct StringPacket : public Packet
{
    //std::string peerName;
    std::string msg;

    // test - 3 diff sizes
    // bool, short, long

    // serialize the string

    StringPacket(std::string msg, PacketHeaderType packetType)
        : msg(msg)
    {
        type = packetType;
    }

    size_t SizeOf() const override
    {
        size_t size = sizeof(type);
        size += msg.length() + 1;
        return size;
    }

    static void serialize(const StringPacket& packet, char* data)
    {
        size_t bufferIdx = 0;
        size_t typeSize = sizeof(packet.type);
        memcpy(&data[bufferIdx], &packet.type, typeSize);

        // Serialize message
        bufferIdx += typeSize;
        size_t messageSize = packet.msg.length() + 1;
        memcpy(&data[bufferIdx], packet.msg.c_str(), messageSize);
        //bufferIdx += messageSize;
    };

    static void deserialize(char* data, size_t dataLength, StringPacket& packet)
    {
        memcpy(&packet.type, &data[0], sizeof(packet.type));

        std::string msg = "";
        for (size_t i = sizeof(packet.type); i < dataLength; ++i)
        {
            if (data[i] == '\0')
            {
                break;
            }
            else
            {
                msg += data[i];
            }
        }
        packet.msg = msg;
    };
};

struct GameOverPacket : public Packet
{
    //std::string peerName; // peer ID is already sent with the message
    bool gameOver;
    //bool won;

    GameOverPacket(bool gameOver)
        : gameOver(gameOver)
    {
        type = GameOver;
    }

    size_t SizeOf() const override
    {
        size_t size = sizeof(type);
        size += sizeof(gameOver);
        return size;
    }

    static void serialize(const GameOverPacket& packet, char* data)
    {
        size_t bufferIdx = 0;
        size_t typeSize = sizeof(packet.type);
        memcpy(&data[bufferIdx], &packet.type, typeSize);

        // Serialize message
        bufferIdx += typeSize;
        size_t intSize = sizeof(packet.gameOver);
        memcpy(&data[bufferIdx], &packet.gameOver, intSize);
    };

    static void deserialize(char* data, size_t dataLength, GameOverPacket& packet)
    {
        memcpy(&packet.type, &data[0], sizeof(packet.type));
        memcpy(&packet.gameOver, &data[sizeof(packet.type)], sizeof(packet.gameOver));
    };
};

//struct ConnectionPacket : public Packet
//{
//    //std::string peerName;
//    std::string peerName;
//
//    ConnectionPacket(std::string peerName)
//        : peerName(peerName)
//    {
//        type = Connection;
//    }
//
//    unsigned int SizeOf() const override
//    {
//        unsigned int size = sizeof(type);
//        size += peerName.length() + 1;
//        return size;
//    }
//};

// Game end (win/lose) packet?