#include "Network.h"
#include <iostream>

bool WayMUD::NetworkInit()
{
#if defined(_WIN32)
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;

	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		std::cout << "WSAStartup Error Code: " << err << std::endl;
		return false;
	}
#endif
	return true;
}

void WayMUD::NetworkShutdown()
{
#if defined(_WIN32)
	WSACleanup();
#endif
}

int WayMUD::NetworkGetLastError()
{
#if defined(_WIN32)
	return WSAGetLastError();
#else
	return errno;
#endif
}