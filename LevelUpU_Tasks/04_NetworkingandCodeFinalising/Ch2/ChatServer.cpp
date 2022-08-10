#include "ChatServer.h"
#include <sstream>

ChatServer::ChatServer(enet_uint32 host, enet_uint16 port)
{
    /* Bind the server to the default localhost.     */
    /* A specific host address can be specified by   */
    /* enet_address_set_host (& address, "x.x.x.x"); */
    address.host = host;
    address.port = port;

    server = enet_host_create(&address, 32, 2, 0, 0);
    if (server == nullptr)
    {
        std::cout << "An error occurred while trying to create an ENet server host.\n" << std::endl;
        exit(EXIT_FAILURE);
    }
}

ChatServer::~ChatServer()
{
    if (server != nullptr) CloseServer();
}

/*
    Connection, disconnection messages would be more readable if I made an info struct that contained
    inputed name (and sent that instead), but it's good enough for now
*/
void ChatServer::HandleEvent()
{
    ENetEvent event;
    std::ostringstream tempMsg;
    std::string msg = "";
    /* Wait up to 1000 milliseconds for an event. */
    while (enet_host_service(server, &event, 1000) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
            tempMsg << "Peer " << event.peer->incomingPeerID << " connected." << "\n\n";
            msg = tempMsg.str();
            std::cout << msg;
            /* Store any relevant client information here. */
            event.peer->data = (void*)"Client information";
            //return event.peer;

            // Let everyone know that someone has joined
            SendAllOtherClients_ClientUpdate(&event, msg);

            break;

        case ENET_EVENT_TYPE_RECEIVE:
            /*std::cout << "A packet of length " << event.packet->dataLength
                      << " containing (" << event.packet->data
                      << ") was received from " << event.peer->data
                      << " on channel " << event.channelID << std::endl;*/

            std::cout << event.packet->data << std::endl;

            // Send the message to everyone else, except the one who sent it
            SendAllOtherClients_ClientUpdate(&event);

            /* Clean up the packet now that we're done using it. */
            enet_packet_destroy(event.packet);
            //return event.peer;
            break;

        case ENET_EVENT_TYPE_DISCONNECT:
            tempMsg << "Peer " << event.peer->incomingPeerID << " disconnected." << "\n\n";
            msg = tempMsg.str();
            std::cout << msg;

            SendAllOtherClients_ClientUpdate(&event, msg);

            /* Reset the peer's client information. */
            event.peer->data = NULL;
            break;

        default:
            std::cout << "Server " << server->address.host << " recieved an event of type "
                << event.type << " which is not handled." << std::endl << std::endl;
            break;
        }
    }
}

void ChatServer::SendStringPacket(std::string msg, ENetPeer* client)
{
    /* Create a reliable packet of size 7 containing "packet\0" */
    ENetPacket* packet = enet_packet_create(msg.c_str(),
        msg.length() + 1,
        ENET_PACKET_FLAG_RELIABLE);


    /* Send the packet to the peer over channel id 0. */
    /* One could also broadcast the packet by         */
    /* enet_host_broadcast (host, 0, packet);         */
    enet_peer_send(client, 0, packet);

    /* One could just use enet_host_service() instead. */
    enet_host_flush(server);
}

void ChatServer::SendPremadeDataPacket(enet_uint8* data, size_t dataSize, ENetPeer* client)
{
    /* Create a reliable packet of size 7 containing "packet\0" */
    ENetPacket* packet = enet_packet_create(data, dataSize, ENET_PACKET_FLAG_RELIABLE);


    /* Send the packet to the peer over channel id 0. */
    /* One could also broadcast the packet by         */
    /* enet_host_broadcast (host, 0, packet);         */
    enet_peer_send(client, 0, packet);

    /* One could just use enet_host_service() instead. */
    enet_host_flush(server);
}

void ChatServer::SendStringPacket_ToAll(std::string msg)
{
    /* Create a reliable packet of size 7 containing "packet\0" */
    ENetPacket* packet = enet_packet_create(msg.c_str(),
        msg.length() + 1,
        ENET_PACKET_FLAG_RELIABLE);


    /* Send the packet to the peer over channel id 0. */
    /* One could also broadcast the packet by         */
    enet_host_broadcast (server, 0, packet);
    //enet_peer_send(client, 0, packet);

    /* One could just use enet_host_service() instead. */
    enet_host_flush(server);
}

void ChatServer::SendAllOtherClients_ClientUpdate(ENetEvent* event)
{
    // Send the message to everyone else, except the one who sent it
    for (int i = 0; i < server->peerCount; i++)
    {
        if (server->peers[i].incomingPeerID != event->peer->incomingPeerID)
        {
            SendPremadeDataPacket(event->packet->data, event->packet->dataLength, &(server->peers[i]));
        }
    }
}

void ChatServer::SendAllOtherClients_ClientUpdate(ENetEvent* event, std::string msg)
{
    // Send the message to everyone else, except the one who sent it
    for (int i = 0; i < server->peerCount; i++)
    {
        if (server->peers[i].incomingPeerID != event->peer->incomingPeerID)
        {
            SendStringPacket(msg, &(server->peers[i]));
        }
    }
}

void ChatServer::CloseServer()
{
    enet_host_destroy(server);
    server = nullptr;
}