#include <enet/enet.h>
#include <iostream>
#include "Section4Header.h"

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

void EnetClientServerParctice()
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
        bool serverCreated = SetUpServer(server, address);

        if (!serverCreated) std::cout << "Could not create server" << std::endl;
        else std::cout << "Server created" << std::endl;
    }
    else if (input == 2)
    {
        bool clientCreated = SetUpClient(client);

        if (!clientCreated) std::cout << "Could not create client" << std::endl;
        else std::cout << "Client created" << std::endl;
    }
    else
    {
        std::cout << "Not a valid input" << std::endl;
    }

    if (server != nullptr) enet_host_destroy(server);
    if (client != nullptr) enet_host_destroy(client);
}

bool SetUpServer(ENetHost* server, ENetAddress address)
{
    server = enet_host_create(&address /* the address to bind the server host to */,
        32      /* allow up to 32 clients and/or outgoing connections */,
        2      /* allow up to 2 channels to be used, 0 and 1 */,
        0      /* assume any amount of incoming bandwidth */,
        0      /* assume any amount of outgoing bandwidth */);
    if (server == nullptr)
    {
        fprintf(stderr,
            "An error occurred while trying to create an ENet server host.\n");
        exit(EXIT_FAILURE);
    }

    return server != nullptr;
}

bool SetUpClient(ENetHost* client)
{
    client = enet_host_create(NULL /* create a client host */,
        1 /* only allow 1 outgoing connection */,
        2 /* allow up 2 channels to be used, 0 and 1 */,
        0 /* assume any amount of incoming bandwidth */,
        0 /* assume any amount of outgoing bandwidth */);
    if (client == nullptr)
    {
        fprintf(stderr,
            "An error occurred while trying to create an ENet client host.\n");
        exit(EXIT_FAILURE);
    }

    return client != nullptr;
}