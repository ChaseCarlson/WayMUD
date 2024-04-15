#pragma once
#include "Socket.h"
#include <memory>

namespace WayMUD
{
	struct Server {
		std::unique_ptr<Socket> serverSocket;
		uint16_t port;
	public:
		Server(uint16_t port);
		bool Open();
		void Loop();
	};
}