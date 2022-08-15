#include <enet/enet.h>
#include "GuessingGamePeer.h"

//Info GuessingGamePeer::Initialize()
//{
//	if (enet_initialize() != 0)
//	{
//		return Info(false, "An error occurred while initializing ENet.");
//	}
//
//	return Info(true, "Successfuly initialized ENet.");
//}

//Info GuessingGamePeer::SendPacket(GuessingGamePacket guessPacket, ENetPeer* peer)
//{
//
//}

Info GuessingGamePeer::SendPacket(Packet* packetInfo, ENetPeer* peer)
{
	Info successInfo = Info(Info::MessageType::Debug);
	ENetPacket* packet;
	Packet::PacketHeaderType packetType = packetInfo->GetType();
	if (packetType == Packet::PacketHeaderType::Invalid)
	{
		Packet* standardPacket = ((Packet*)packetInfo);

		size_t dataSize = standardPacket->SizeOf();
		char* data = new char[dataSize];

		Packet::serialize(*standardPacket, data);

		packet = enet_packet_create(data, sizeof(*packetInfo), ENET_PACKET_FLAG_RELIABLE);
		successInfo.msg = "Successfully sent packet of type Invalid";
	}

	else if (packetType == Packet::PacketHeaderType::Connection)
	{
		StringPacket* connectionPacket = ((StringPacket*)packetInfo);

		size_t dataSize = connectionPacket->SizeOf();
		char* data = new char[dataSize];

		StringPacket::serialize(*connectionPacket, data);

		packet = enet_packet_create(data, dataSize, ENET_PACKET_FLAG_RELIABLE);
		successInfo.msg = "Successfully sent packet of type Connection";
	}

	else if (packetType == Packet::PacketHeaderType::Guess)
	{
		GuessingPacket* guessingPacket = ((GuessingPacket*)packetInfo);

		size_t dataSize = guessingPacket->SizeOf();
		char* data = new char[dataSize];

		GuessingPacket::serialize(*guessingPacket, data);
		
		packet = enet_packet_create(data, sizeof(*guessingPacket), ENET_PACKET_FLAG_RELIABLE);
		successInfo.msg = "Successfully sent packet of type Guess";
	}

	// same as connection packet
	else if (packetType == Packet::PacketHeaderType::ServerMsg || packetType == Packet::PacketHeaderType::ClientMsg)
	{
		StringPacket* stringPacket = ((StringPacket*)packetInfo);

		size_t dataSize = stringPacket->SizeOf();
		char* data = new char[dataSize];

		StringPacket::serialize(*stringPacket, data);

		packet = enet_packet_create(data, stringPacket->SizeOf(), ENET_PACKET_FLAG_RELIABLE);
		successInfo.msg = "Successfully sent packet of type String";
	}

	else if (packetType == Packet::PacketHeaderType::GameOver)
	{
		GameOverPacket* gameOverPacket = ((GameOverPacket*)packetInfo);

		size_t dataSize = gameOverPacket->SizeOf();
		char* data = new char[dataSize];

		GameOverPacket::serialize(*gameOverPacket, data);

		packet = enet_packet_create(data, sizeof(*gameOverPacket), ENET_PACKET_FLAG_RELIABLE);
		successInfo.msg = "Successfully sent packet of type GameOver";
	}

	else
	{
		packet = enet_packet_create(packetInfo, sizeof(*packetInfo), ENET_PACKET_FLAG_RELIABLE);
		successInfo.msg = "Successfully sent packet of type UNDEFINED";
	}

	/* Send the packet to the peer over channel id 0. */
	/* One could also broadcast the packet by         */
	/* enet_host_broadcast (host, 0, packet);         */
	int success = enet_peer_send(peer, 0, packet);

	/* One could just use enet_host_service() instead. */
	enet_host_flush(host);

	if (success < 0)
	{
		successInfo.success = false;
		successInfo.msg = "Failed to send packet";
	}
	else
	{
		successInfo.success = true;
		//successInfo.msg = "Packet successfully sent";
	}

	return successInfo;
}

Info GuessingGamePeer::SendEventData(enet_uint8* data, size_t dataSize, ENetPeer* peer)
{
	Info successInfo = Info(Info::MessageType::Debug);

	ENetPacket* packet = enet_packet_create(data, dataSize, ENET_PACKET_FLAG_RELIABLE);

	/* Send the packet to the peer over channel id 0. */
	/* One could also broadcast the packet by         */
	/* enet_host_broadcast (host, 0, packet);         */
	int success = enet_peer_send(peer, 0, packet);

	/* One could just use enet_host_service() instead. */
	enet_host_flush(host);

	if (success < 0)
	{
		successInfo.success = false;
		successInfo.msg = "Failed to send packet";
	}
	else
	{
		successInfo.success = true;
		//successInfo.msg = "Packet successfully sent";
	}

	return successInfo;
}

Info GuessingGamePeer::SendPacket_ToAll(Packet* packetInfo)
{
	Info successInfo = Info(Info::MessageType::Debug);
	ENetPacket* packet;
	Packet::PacketHeaderType packetType = packetInfo->GetType();
	if (packetType == Packet::PacketHeaderType::Invalid)
	{
		Packet* standardPacket = ((Packet*)packetInfo);

		size_t dataSize = standardPacket->SizeOf();
		char* data = new char[dataSize];

		Packet::serialize(*standardPacket, data);

		packet = enet_packet_create(data, sizeof(*packetInfo), ENET_PACKET_FLAG_RELIABLE);
		successInfo.msg = "Successfully sent packet of type Invalid";
	}

	else if (packetType == Packet::PacketHeaderType::Connection)
	{
		StringPacket* connectionPacket = ((StringPacket*)packetInfo);

		size_t dataSize = connectionPacket->SizeOf();
		char* data = new char[dataSize];

		StringPacket::serialize(*connectionPacket, data);

		packet = enet_packet_create(data, dataSize, ENET_PACKET_FLAG_RELIABLE);
		successInfo.msg = "Successfully sent packet of type Connection";
	}

	else if (packetType == Packet::PacketHeaderType::Guess)
	{
		GuessingPacket* guessingPacket = ((GuessingPacket*)packetInfo);

		size_t dataSize = guessingPacket->SizeOf();
		char* data = new char[dataSize];

		GuessingPacket::serialize(*guessingPacket, data);

		packet = enet_packet_create(data, sizeof(*guessingPacket), ENET_PACKET_FLAG_RELIABLE);
		successInfo.msg = "Successfully sent packet of type Guess";
	}

	// same as connection packet
	else if (packetType == Packet::PacketHeaderType::ServerMsg || packetType == Packet::PacketHeaderType::ClientMsg)
	{
		StringPacket* stringPacket = ((StringPacket*)packetInfo);

		size_t dataSize = stringPacket->SizeOf();
		char* data = new char[dataSize];

		StringPacket::serialize(*stringPacket, data);

		packet = enet_packet_create(data, stringPacket->SizeOf(), ENET_PACKET_FLAG_RELIABLE);
		successInfo.msg = "Successfully sent packet of type String";
	}
	else if (packetType == Packet::PacketHeaderType::GameOver)
	{
		GameOverPacket* gameOverPacket = ((GameOverPacket*)packetInfo);

		size_t dataSize = gameOverPacket->SizeOf();
		char* data = new char[dataSize];

		GameOverPacket::serialize(*gameOverPacket, data);

		packet = enet_packet_create(data, sizeof(*gameOverPacket), ENET_PACKET_FLAG_RELIABLE);
		successInfo.msg = "Successfully sent packet of type GameOver";
	}

	else
	{
		packet = enet_packet_create(packetInfo, sizeof(*packetInfo), ENET_PACKET_FLAG_RELIABLE);
		successInfo.msg = "Successfully sent packet of type UNDEFINED";
	}

	/* Send the packet to the peer over channel id 0. */
	/* One could also broadcast the packet by         */
	/* enet_host_broadcast (host, 0, packet);         */
	enet_host_broadcast(host, 0, packet);

	/* One could just use enet_host_service() instead. */
	enet_host_flush(host);

	return successInfo;
}

void GuessingGamePeer::CloseConnection()
{ 
	if (host != nullptr) 
	{ 
		delete host;
		host = nullptr; 
	} 
}