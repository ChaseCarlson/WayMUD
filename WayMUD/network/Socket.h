#pragma once
#include "Network.h"
#include <cstdint>

namespace WayMUD
{
	struct Socket {
		SOCKET_DESCRIPTOR sock_fd;
		bool SetNonBlocking();
	public:
		Socket();
		Socket(SOCKET_DESCRIPTOR fd);
		~Socket();
		SOCKET_DESCRIPTOR GetDescriptor();
	};
}