#include "GuessingGameServer.h"
#include <sstream>

// TODO:
// All thhat is left is for the game to actually end + play again?

GuessingGameServer::GuessingGameServer(enet_uint32 addrHost, enet_uint16 addrPort)
{
    /* Bind the server to the default localhost.     */
    /* A specific host address can be specified by   */
    /* enet_address_set_host (& address, "x.x.x.x"); */
    address.host = addrHost;
    address.port = addrPort;

    host = enet_host_create(&address, 32, 2, 0, 0);
    if (host == nullptr)
    {
        //An error occurred while trying to create an ENet server host.
        exit(EXIT_FAILURE);
    }

    type = ConnectionType::Server;

    srand(time(NULL));
    ChooseRandomNumber();
    //gameWon = false;
}

GuessingGameServer::~GuessingGameServer()
{
    CloseConnection();
}

// all game checking logic
 // keep track of "players" - name, peerID
 // turn based? tell other player to chill if they guess on not their turn
Info GuessingGameServer::HandleEvent()
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
        case ENET_EVENT_TYPE_CONNECT:
            successInfo.success = true;
            successInfo.type = Info::MessageType::Debug;
            msg << "Peer " << event.peer->incomingPeerID << " connected.";
            successInfo.msg = msg.str();

            enet_packet_destroy(event.packet);
            return successInfo;

        case ENET_EVENT_TYPE_RECEIVE:
            Packet::deserialize((char*)event.packet->data, event.packet->dataLength, packet);

            //packet = (Packet*)(event.packet->data);

            /*if (packet)
            {*/
                switch (packet.GetType())
                {
                case Packet::PacketHeaderType::Invalid:
                    successInfo.success = false;
                    successInfo.type = Info::MessageType::Status;
                    successInfo.msg = "Invalid packet type recieved.";
                    break;

                case Packet::PacketHeaderType::Guess:
                     successInfo = GuessEvent(&event);
                     break;

                case Packet::PacketHeaderType::ClientMsg:
                    successInfo = StringEvent(&event);
                    //if (successInfo.success) SendAllOtherClients_ClientUpdate(&event);  // losing Info from this call
                    break;

                case Packet::PacketHeaderType::Connection:
                    successInfo = ConnectionEvent(&event);
                    //if (successInfo.success) SendAllOtherClients_ClientUpdate(&event);  // losing Info from this call
                    break;

                default:
                    successInfo.success = false;
                    successInfo.type = Info::MessageType::Status;
                    successInfo.msg = "Unhandled type for recieved packet.";
                    break;
                }
            /*}
            else
            {
                successInfo.success = false;
                successInfo.type = Info::MessageType::Status;
                successInfo.msg = "Recieved something, but it wasn't a packet";
            }*/

            enet_packet_destroy(event.packet);
            return successInfo;

        case ENET_EVENT_TYPE_DISCONNECT:
            successInfo = DisconnectEvent(&event);

            if (successInfo.success) SendAllOtherClients_ClientUpdate(&event);  // losing Info from this call

            enet_packet_destroy(event.packet);
            return successInfo;

        default:
            successInfo.success = false;
            successInfo.type = Info::MessageType::Debug;
            msg << "Server recieved an event of type " << event.type << " (from peer " << event.peer->incomingPeerID << ") which is not handled." << std::endl;
            successInfo.msg = msg.str();
            return successInfo;
        }
    }

    return successInfo;
}

Info GuessingGameServer::SendAllOtherClients_ClientUpdate(ENetEvent* event)
{
    Info successInfo = Info();
    Info returnInfo = Info(Info::MessageType::Debug, true, "Sent all other clients the update");
    // Send the message to everyone else, except the one who sent it
    // not very efficient
    int numPeers = host->connectedPeers;

    for (int i = 0; i < numPeers; i++)
    {
        if (host->peers[i].incomingPeerID != event->peer->incomingPeerID)
        {
            successInfo = SendEventData(event->packet->data, event->packet->dataLength, &(host->peers[i]));

            if (!successInfo.success)
            {
                returnInfo.success = false;
                returnInfo.msg = "Failed to send all other clients the update";
            }
        }
    }

    return returnInfo;
}

void GuessingGameServer::CloseConnection()
{
	GuessingGamePeer::CloseConnection();
}

////////////////////////////////////////////////////////////////////////////////////////

void GuessingGameServer::ChooseRandomNumber()
{
    gameWon = false;
    numberToGuess = rand() % 100 + 1;
}

Info GuessingGameServer::GuessEvent(ENetEvent* event)
{
    Info successInfo = Info(Info::MessageType::GameInfo);
    std::ostringstream msg;

    GuessingPacket guessingPacket = GuessingPacket(0);
    GuessingPacket::deserialize((char*)event->packet->data, event->packet->dataLength, guessingPacket);

    if (peerNames.count(event->peer->incomingPeerID))
    {
        // is a player
        successInfo.success = true;
        msg << peerNames[event->peer->incomingPeerID] << " guessed " << guessingPacket.guess << ". ";

        // if the guessed number is higher
        if (guessingPacket.guess > numberToGuess)
        {
            msg << "The correct number is LOWER.";
        }

        // if lower
        else if (guessingPacket.guess < numberToGuess)
        {
            msg << "The correct number is HIGHER.";
        }

        // if correct
        else
        {
            gameWon = true;
            msg << "That is the CORRECT NUMBER!\n";
            msg << peerNames[event->peer->incomingPeerID] << " has won!\n";
            msg << "Would you like to play again? (\'yes\' / \'no\')";
        }
        
        successInfo.msg = msg.str();
        std::string sendMsg = msg.str();

        StringPacket stringPacket = StringPacket(sendMsg,Packet::PacketHeaderType::ServerMsg);

        SendPacket_ToAll(&stringPacket);
    }
    else
    {
        successInfo.success = false;
        msg << "Peer " << event->peer->incomingPeerID << " guessed " << guessingPacket.guess << " even though they are not a player.";
        successInfo.msg = msg.str();
    }

    return successInfo;
}

Info GuessingGameServer::StringEvent(ENetEvent* event)
{
    Info successInfo = Info(Info::MessageType::PlayerMsg);
    std::ostringstream msg;

    StringPacket stringPacket = StringPacket("FillerMsg", Packet::PacketHeaderType::ClientMsg);
    StringPacket::deserialize((char*)event->packet->data, event->packet->dataLength, stringPacket);

    if (peerNames.count(event->peer->incomingPeerID))
    {
        // is a player
        successInfo.success = true;
        msg << peerNames[event->peer->incomingPeerID] << ": " << stringPacket.msg;
        successInfo.msg = msg.str();

        std::string sendMsg = msg.str();

        if (gameWon && stringPacket.msg == "yes")
        {
            // choose new random number;
            ChooseRandomNumber();
            sendMsg += "\nRestarting the game. A new number has been selected.";
        }

        successInfo.msg = sendMsg;

        StringPacket returnStringPacket = StringPacket(sendMsg, Packet::PacketHeaderType::ClientMsg);
        SendPacket_ToAll(&returnStringPacket);

        // after, if the game is ended, send as such
        if (gameWon && stringPacket.msg == "no")
        {
            successInfo.msg += "\nEnding the game.";

            successInfo.gameOver = true;
            
            GameOverPacket gameOverPacket = GameOverPacket(true);
            SendPacket_ToAll(&gameOverPacket);
        }
    }
    else
    {
        successInfo.success = false;
        successInfo.type = Info::MessageType::Status;
        msg << "Peer " << event->peer->incomingPeerID << " said " << stringPacket.msg << " even though they are not a player.";
        successInfo.msg = msg.str();
    }
    return successInfo;
}

Info GuessingGameServer::ConnectionEvent(ENetEvent* event)
{
    Info successInfo = Info(Info::MessageType::Status);

    StringPacket connectionPacket = StringPacket("FillerMsg", Packet::PacketHeaderType::ClientMsg);
    StringPacket::deserialize((char*)event->packet->data, event->packet->dataLength, connectionPacket);

    // The count would be 1 if the element is indeed present in the map
    if (peerNames.count(event->peer->incomingPeerID) < 1)
    {
        peerNames.insert({ event->peer->incomingPeerID, connectionPacket.msg });
        successInfo.success = true;
        successInfo.msg = connectionPacket.msg + " has connected. Welcome!";

        std::string sendMsg = successInfo.msg;

        StringPacket stringPacket = StringPacket(sendMsg, Packet::PacketHeaderType::ServerMsg);

        SendPacket_ToAll(&stringPacket);
    }
    else
    {
        successInfo.success = false;
        successInfo.msg = connectionPacket.msg + " has already connected before.";
    }

    return successInfo;
}

Info GuessingGameServer::DisconnectEvent(ENetEvent* event)
{
    Info successInfo = Info(Info::MessageType::Status);

    if (peerNames.count(event->peer->incomingPeerID) < 1)
    {
        // never connected in the first place
        successInfo.success = false;
        std::ostringstream msg;
        msg << "Peer " << event->peer->incomingPeerID << " has never connected before.";
        successInfo.msg = msg.str();
    }
    else
    {
        // disconnect
        successInfo.success = true;
        successInfo.msg = peerNames[event->peer->incomingPeerID] + " has disconnected.";
        peerNames.erase(event->peer->incomingPeerID);
    }

    return successInfo;
}