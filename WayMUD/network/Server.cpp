#include "Server.h"
#include <iostream>

WayMUD::Server::Server(uint16_t port) : port(port)
{
	serverSocket = std::make_unique<Socket>();
}

bool WayMUD::Server::Open()
{
	sockaddr_in6 addr = {};
	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(port);
	addr.sin6_addr = in6addr_any;

	int off = 0;
	if (setsockopt(serverSocket->GetDescriptor(), IPPROTO_IPV6, IPV6_V6ONLY, (char*)&off, sizeof(off)) == SOCKET_ERROR) {
		perror("setsockopt");
		closesocket(serverSocket->GetDescriptor());
		return false;
	}

	int bindStatus = bind(serverSocket->GetDescriptor(), (sockaddr*)&addr, sizeof(addr));
	if (bindStatus == SOCKET_ERROR) return false;

	int listenStatus = listen(serverSocket->GetDescriptor(), 5);
	if (listenStatus != 0) return false;

	return true;

}

void WayMUD::Server::Loop()
{
	sockaddr_in6 newAddr;
	int addrLen = sizeof(newAddr);
	SOCKET_DESCRIPTOR clientFd = accept(serverSocket->GetDescriptor(), (sockaddr*)&newAddr, &addrLen);
	if (ISVALIDSOCKET(clientFd)) {
		std::cout << "Connection accepted" << std::endl;
		const char* msg = "Welcome\r\n";
		send(clientFd, msg, strlen(msg), 0);
		this->clients.push_back(std::make_shared<Client>(std::make_shared<Socket>(clientFd)));
	}
	else {
		if (!ISERROR(ERR_WOULDBLOCK))
		{
			std::cerr << "Socket accept error" << std::endl;
		}
	}

	for (auto it = clients.begin(); it != clients.end(); )
	{
		std::shared_ptr<Client> client = *it;
		std::shared_ptr<Socket> socket = client->getSocket();
		char buffer[512];
		int ret = recvfrom(socket->GetDescriptor(), buffer, sizeof(buffer), 0, nullptr, nullptr);
		if (ret > 0)
		{
			SendToAllExcept(client, buffer, ret);
			++it;
		}
		else if (ret == 0)
		{
			it = clients.erase(it);
		}
		else if (!IFWOULDBLOCK())
		{
			std::cerr << "Socket receive error " << GetLastError() << std::endl;
			++it;
		}
		else
		{
			++it;
		}
	}
}

void WayMUD::Server::SendToAllExcept(std::shared_ptr<Client> excludedClient, char* buf, size_t len)
{
	for (std::shared_ptr<Client> client : clients)
	{
		if (client == excludedClient) continue;
		sendto(client->getSocket()->GetDescriptor(), buf, len, 0, 0, 0);
	}
}
