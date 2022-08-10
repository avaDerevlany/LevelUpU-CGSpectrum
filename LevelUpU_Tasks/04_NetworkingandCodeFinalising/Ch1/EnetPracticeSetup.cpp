#include <enet/enet.h>
#include <iostream>
#include "../Section4Header.h"

int EnetPractice()
{
    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        std::cout << "An error occurred while initializing ENet." << std::endl;
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);

    return EXIT_SUCCESS;
}

void EnetClientServerPractice()
{
    ENetAddress address;
    ENetHost* server = nullptr;
    ENetHost* client = nullptr;

    /* Bind the server to the default localhost.     */
    /* A specific host address can be specified by   */
    /* enet_address_set_host (& address, "x.x.x.x"); */
    address.host = ENET_HOST_ANY;
    /* Bind the server to port 1234. */
    address.port = 1234;

    std::cout << "1) Set up server" << std::endl;
    std::cout << "2) Set up client" << std::endl;
    int input;
    std::cin >> input;

    if (input == 1)
    {
        server = SetUpServer(server, address);

        if (server == nullptr) std::cout << "Could not create server" << std::endl;
        else std::cout << "Server created" << std::endl;
    }
    else if (input == 2)
    {
        client = SetUpClient(client);

        if (client == nullptr) std::cout << "Could not create client" << std::endl;
        else std::cout << "Client created" << std::endl;
    }
    else
    {
        std::cout << "Not a valid input" << std::endl;
    }

    bool msgOnce = false;

    // SERVER
    if (server != nullptr)
    {
        /*std::cout << "Waiting for client to connect..." << std::endl;
        while (client == nullptr)
        {

        }
        std::cout << "Client connected!" << std::endl;*/

        ENetPeer* clientPeer = nullptr;

        while (1)
        {
            clientPeer = HandleEvent(server);

            if (clientPeer != nullptr && !msgOnce)
            {
                SendPacket(clientPeer, server);
                clientPeer = nullptr;
                msgOnce = true;
            }
        }

        enet_host_destroy(server);
    }
    
    // CLIENT
    if (client != nullptr)
    {
        ENetPeer* serverPeer = ConnectToServer(client, address);

        while (1)
        {
            if (serverPeer != nullptr && !msgOnce)
            {
                SendPacket(serverPeer, client);
                serverPeer = nullptr;
                msgOnce = true;
            }

            serverPeer = HandleEvent(client);
        }

        enet_host_destroy(client);
    }
}

ENetHost* SetUpServer(ENetHost* server, ENetAddress address)
{
    server = enet_host_create(&address /* the address to bind the server host to */,
        32      /* allow up to 32 clients and/or outgoing connections */,
        2      /* allow up to 2 channels to be used, 0 and 1 */,
        0      /* assume any amount of incoming bandwidth */,
        0      /* assume any amount of outgoing bandwidth */);
    if (server == nullptr)
    {
        std::cout << "An error occurred while trying to create an ENet server host.\n";
        exit(EXIT_FAILURE);
    }

    return server;
}

ENetHost* SetUpClient(ENetHost* client)
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

    return client;
}

ENetPeer* HandleEvent(ENetHost* host)
{
    ENetEvent event;
    /* Wait up to 1000 milliseconds for an event. */
    while (enet_host_service(host, &event, 1000) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
            std::cout << "A new client connected from "
                      << event.peer->address.host << ":"
                      << event.peer->address.port << std::endl;
            /* Store any relevant client information here. */
            event.peer->data = (void*)"Client information";
            return event.peer;

        case ENET_EVENT_TYPE_RECEIVE:
            std::cout << "A packet of length " << event.packet->dataLength
                      << " containing (" << event.packet->data
                      << ") was received from " << event.peer->data
                      << " on channel " << event.channelID << std::endl;
            /* Clean up the packet now that we're done using it. */
            enet_packet_destroy(event.packet);
            return event.peer;

        case ENET_EVENT_TYPE_DISCONNECT:
            std::cout << event.peer->data << " disconnected." << std::endl;
            /* Reset the peer's client information. */
            event.peer->data = NULL;
        }
    }
    return nullptr;
}

ENetPeer* ConnectToServer(ENetHost* client, ENetAddress address)
{
    ENetEvent event;
    ENetPeer* peer;
    /* Connect to some.server.net:1234. */
    enet_address_set_host(&address, "localhost");
    address.port = 1234;
    /* Initiate the connection, allocating the two channels 0 and 1. */
    peer = enet_host_connect(client, &address, 2, 0);
    if (peer == NULL)
    {
        std::cout << "No available peers for initiating an ENet connection.\n";
        exit(EXIT_FAILURE);
    }
    /* Wait up to 5 seconds for the connection attempt to succeed. */
    if (enet_host_service(client, &event, 5000) > 0 &&
        event.type == ENET_EVENT_TYPE_CONNECT)
    {
        std::cout << "Connection to localhost:1234 succeeded." << std::endl;

    }
    else
    {
        /* Either the 5 seconds are up or a disconnect event was */
        /* received. Reset the peer in the event the 5 seconds   */
        /* had run out without any significant event.            */
        enet_peer_reset(peer);
        std::cout << "Connection to localhost:1234 failed." << std::endl;
    }

    return peer;
}

void SendPacket(ENetPeer* client, ENetHost* host)
{
    /* Create a reliable packet of size 7 containing "packet\0" */
    ENetPacket* packet = enet_packet_create("packet",
                        strlen("packet") + 1,
                        ENET_PACKET_FLAG_RELIABLE);

    /* Extend the packet so and append the string "foo", so it now */
    /* contains "packetfoo\0"                                      */
    //enet_packet_resize(packet, strlen("packetfoo") + 1);
    //strcpy(&packet->data[strlen("packet")], "foo");

    /* Send the packet to the peer over channel id 0. */
    /* One could also broadcast the packet by         */
    /* enet_host_broadcast (host, 0, packet);         */
    enet_peer_send(client, 0, packet);

    /* One could just use enet_host_service() instead. */
    enet_host_flush(host);
}