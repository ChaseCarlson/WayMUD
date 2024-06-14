#pragma once
#include "Socket.h"
#include <memory>
#include <vector>
#include "Client.h"

namespace WayMUD
{
	struct Server {
		std::unique_ptr<Socket> serverSocket;
		std::vector<std::shared_ptr<Client>> clients;
		uint16_t port;
	public:
		Server(uint16_t port);
		bool Open();
		void Loop();
		void SendToAllExcept(std::shared_ptr<Client> excludedClient, char* buf, size_t len);
	};
}