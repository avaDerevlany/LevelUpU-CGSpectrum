#include "ChatClient.h"
#include <string>

ChatClient::ChatClient()
{
    client = enet_host_create(NULL /* create a client host */,
        1 /* only allow 1 outgoing connection */,
        2 /* allow up 2 channels to be used, 0 and 1 */,
        0 /* assume any amount of incoming bandwidth */,
        0 /* assume any amount of outgoing bandwidth */);
    if (client == nullptr)
    {
        std::cout << "An error occurred while trying to create an ENet client host.\n";
        exit(EXIT_FAILURE);
    }
}

ChatClient::~ChatClient()
{
    if (client != nullptr || server != nullptr) CloseClient();
}

bool ChatClient::ConnectToChatServer(enet_uint32 host, enet_uint16 port)
{
    ENetAddress serverAddress;
    serverAddress.host = host;
    serverAddress.port = port;

    ENetEvent event;
    //ENetPeer* server;
    /* Connect to some.server.net:1234. */
    enet_address_set_host(&serverAddress, "localhost");
    serverAddress.port = 1234;


    /* Initiate the connection, allocating the two channels 0 and 1. */
    server = enet_host_connect(client, &serverAddress, 2, 0);
    if (server == NULL)
    {
        std::cout << "No available peers for initiating an ENet connection.\n" << std::endl;
        exit(EXIT_FAILURE);
        return false;
    }
    /* Wait up to 5 seconds for the connection attempt to succeed. */
    if (enet_host_service(client, &event, 5000) > 0 &&
        event.type == ENET_EVENT_TYPE_CONNECT)
    {
        std::cout << "Connection to " << serverAddress.host << ":" << serverAddress.port << " succeeded.\n" << std::endl;
        return true;
    }
    else
    {
        /* Either the 5 seconds are up or a disconnect event was */
        /* received. Reset the peer in the event the 5 seconds   */
        /* had run out without any significant event.            */
        enet_peer_reset(server);
        std::cout << "Connection to " << serverAddress.host << ":" << serverAddress.port << " failed.\n" << std::endl;
        return false;
    }
}

void ChatClient::HandleEvent()
{
    ENetEvent event;
    /* Wait up to 1000 milliseconds for an event. */
    while (enet_host_service(client, &event, 1000) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_RECEIVE:
            std::cout << event.packet->data << std::endl;
            enet_packet_destroy(event.packet);
            break;

        default:
            std::cout << "Client " << client->address.host << " recieved an event of type "
                      << event.type << " which is not handled." << std::endl;
            break;
        }
    }
}

void ChatClient::SendStringPacket(std::string msg)
{
    /* Create a reliable packet of size 7 containing "packet\0" */
    ENetPacket* packet = enet_packet_create(msg.c_str(),
        msg.length() + 1,
        ENET_PACKET_FLAG_RELIABLE);


    /* Send the packet to the peer over channel id 0. */
    /* One could also broadcast the packet by         */
    /* enet_host_broadcast (host, 0, packet);         */
    enet_peer_send(server, 0, packet);

    /* One could just use enet_host_service() instead. */
    enet_host_flush(client);
}

void ChatClient::CloseClient()
{
    enet_host_destroy(client);
    client = nullptr;
    server = nullptr;
}