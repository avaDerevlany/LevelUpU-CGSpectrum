#include <enet/enet.h>
#include <sstream>
#include "GuessingGameClient.h"

GuessingGameClient::GuessingGameClient()
{
    host = enet_host_create(NULL /* create a client host */,
        1 /* only allow 1 outgoing connection */,
        2 /* allow up 2 channels to be used, 0 and 1 */,
        0 /* assume any amount of incoming bandwidth */,
        0 /* assume any amount of outgoing bandwidth */);
    if (host == nullptr)
    {
        // An error occurred while trying to create an ENet client host.
        exit(EXIT_FAILURE);
    }

    type = ConnectionType::Client;
}

GuessingGameClient::~GuessingGameClient()
{
    CloseConnection();
}

Info GuessingGameClient::ConnectToServer(enet_uint32 addrHost, enet_uint16 addrPort)
{
    if (host == nullptr)
    {
        return Info(Info::MessageType::Status, false, "An error occurred while trying to create an ENet client host. Host not created.");
    }

    // Server Address
    ENetAddress serverAddress;
    serverAddress.host = addrHost;
    serverAddress.port = addrPort;
    enet_address_set_host(&serverAddress, "localhost");
    serverAddress.port = 1234;

    /* Initiate the connection, allocating the two channels 0 and 1. */
    server = enet_host_connect(host, &serverAddress, 2, 0);

    ENetEvent event;

    if (server == NULL)
    {
        exit(EXIT_FAILURE);
        return Info(Info::MessageType::Status, false, "No available peers for initiating an ENet connection.");
    }
    /* Wait up to 5 seconds for the connection attempt to succeed. */
    if (enet_host_service(host, &event, 5000) > 0 &&
        event.type == ENET_EVENT_TYPE_CONNECT)
    {
        std::ostringstream msg;
        msg << "Connection to " << serverAddress.host << ":" << serverAddress.port << " succeeded.";
        return Info(Info::MessageType::Status, true, msg.str());
    }
    else
    {
        /* Either the 5 seconds are up or a disconnect event was */
        /* received. Reset the peer in the event the 5 seconds   */
        /* had run out without any significant event.            */
        enet_peer_reset(server);
        std::ostringstream msg;
        msg << "Connection to " << serverAddress.host << ":" << serverAddress.port << " failed.\n" << std::endl;
        return Info(Info::MessageType::Status, false, msg.str());
    }
}

Info GuessingGameClient::HandleEvent()
{
    Info successInfo = Info();
    std::ostringstream msg;

    ENetEvent event;
    Packet packet = Packet();

    /* Wait up to 1000 milliseconds for an event. */
    while (enet_host_service(host, &event, 1000) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_RECEIVE:
            Packet::deserialize((char*)event.packet->data, event.packet->dataLength, packet);
            
            /*if (packet)
            {*/
                switch (packet.GetType())
                {
                case Packet::PacketHeaderType::Invalid:
                    successInfo.success = false;
                    successInfo.type = Info::MessageType::Debug;
                    successInfo.msg = "Invalid packet type recieved.";
                    break;

                /*case Packet::PacketHeaderType::Guess:
                    successInfo.success = true;
                    successInfo.msg = ((GuessingPacket*)packet)->peerName + ": " 
                                      + std::to_string(((GuessingPacket*)packet)->guess);
                    break;*/

                case Packet::PacketHeaderType::ServerMsg:
                    successInfo = StringEvent(&event, Packet::PacketHeaderType::ServerMsg);
                    break;

                case Packet::PacketHeaderType::ClientMsg:
                    successInfo = StringEvent(&event, Packet::PacketHeaderType::ClientMsg);
                    break;

                case Packet::PacketHeaderType::GameOver:
                    successInfo = BoolEvent(&event);
                    break;

                default:
                    successInfo.success = false;
                    successInfo.type = Info::MessageType::Debug;
                    successInfo.msg = "Unhandled type for recieved packet.";
                    break;
                }
            /*}
            else
            {
                successInfo.success = false;
                successInfo.type = Info::MessageType::Debug;
                successInfo.msg = "Recieved something, but it wasn't a packet";
            }*/

            enet_packet_destroy(event.packet);
            return successInfo;

        case ENET_EVENT_TYPE_DISCONNECT:
            successInfo.success = true;
            successInfo.type = Info::MessageType::Status;
            successInfo.msg = "Server disconnected...";
            return successInfo;

        default:
            successInfo.success = false;
            successInfo.type = Info::MessageType::Debug;
            msg << "Client " << host->address.host << " recieved an event of type "
                << event.type << " which is not handled." << std::endl;
            successInfo.msg = msg.str();
            return successInfo;
        }
    }

    return successInfo;
}

//Info GuessingGameClient::SendPacket(GuessingGamePacket guessPacket)
//{
//
//}

Info GuessingGameClient::StringEvent(ENetEvent* event, Packet::PacketHeaderType type)
{
    Info successInfo = Info(Info::MessageType::GameInfo, true);

    if (type == Packet::PacketHeaderType::ClientMsg)
    {
        successInfo.type = Info::MessageType::PlayerMsg;
    }

    std::ostringstream msg;

    StringPacket stringPacket = StringPacket("FillerMsg", type);
    StringPacket::deserialize((char*)event->packet->data, event->packet->dataLength, stringPacket);

    successInfo.msg = stringPacket.msg;

    return successInfo;
}

Info GuessingGameClient::BoolEvent(ENetEvent* event)
{
    Info successInfo = Info(Info::MessageType::GameInfo, true);

    std::ostringstream msg;

    GameOverPacket gameOverPacket = GameOverPacket(true);
    GameOverPacket::deserialize((char*)event->packet->data, event->packet->dataLength, gameOverPacket);

    if (gameOverPacket.gameOver)
    {
        successInfo.msg = "Game Over. Thank you for playing!";
        successInfo.gameOver = true;
    }

    return successInfo;
}

void GuessingGameClient::CloseConnection()
{
	GuessingGamePeer::CloseConnection();

	if (server != nullptr)
	{
		server = nullptr;
	}
}
