#include "Server.h"
#include <iostream>

WayMUD::Server::Server(uint16_t port) : port(port)
{
	serverSocket = std::make_unique<Socket>();
}

bool WayMUD::Server::Open()
{
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;

	int bindStatus = bind(serverSocket->GetDescriptor(), (sockaddr*)&addr, sizeof(addr));
	if (bindStatus != 0) return false;
	int listenStatus = listen(serverSocket->GetDescriptor(), 5);
	if (listenStatus != 0) return false;

	return true;

}

void WayMUD::Server::Loop()
{
	sockaddr_in newAddr;
	int addrLen = sizeof(newAddr);
	SOCKET_DESCRIPTOR clientFd = accept(serverSocket->GetDescriptor(), (sockaddr*)&newAddr, &addrLen);
	if (ISVALIDSOCKET(clientFd)) {
		std::cout << "Connection accepted" << std::endl;
		const char* msg = "Welcome";
		send(clientFd, msg, strlen(msg), 0);
	}
	else {
		if (!ISERROR(ERR_WOULDBLOCK))
		{
			std::cerr << "Socket accept error" << std::endl;
		}
	}
}
