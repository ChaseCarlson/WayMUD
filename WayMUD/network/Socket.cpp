#include "Socket.h"
#include <iostream>

bool WayMUD::Socket::SetNonBlocking()
{
#if defined(_WIN32)
	unsigned long mode = 1;
	if (ioctlsocket(sock_fd, FIONBIO, &mode) != 0) {
		std::cerr << "ioctlsocket failed with error: " << WSAGetLastError() << std::endl;
		return false;
	}
#else
	if ((flags = fcntl(sockfd, F_GETFL, 0)) == -1) {
		flags = 0;
	}

	// Set socket to non-blocking
	if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
		std::cerr << "Error setting non-blocking" << std::endl;
		return false;
	}
#endif
	return true;
}

WayMUD::Socket::Socket()
{
	this->sock_fd = socket(AF_INET6, SOCK_STREAM, 0);
	SetNonBlocking();
}

WayMUD::Socket::Socket(SOCKET_DESCRIPTOR fd)
{
	this->sock_fd = fd;
	SetNonBlocking();
}

WayMUD::Socket::~Socket()
{
	SOCKET_CLOSE(this->sock_fd);
}

SOCKET_DESCRIPTOR WayMUD::Socket::GetDescriptor()
{
	return sock_fd;
}
