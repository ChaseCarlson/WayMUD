#pragma once

#if defined(_WIN32)
	#include "winsock2.h"
	#pragma comment(lib, "Ws2_32.lib")
	#include <WS2tcpip.h>


	#define SOCKET_DESCRIPTOR SOCKET
	#define ERR_WOULDBLOCK WSAEWOULDBLOCK
	#define ERR_CONNECTION_ABORTED WSAECONNABORTED

	#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
	#define ISERROR(error) (WSAGetLastError() == error)
	#define IFWOULDBLOCK() (WSAGetLastError() == ERR_WOULDBLOCK)
	#define SOCKET_CLOSE(fd) closesocket(fd)
#else
	#define SOCKET_DESCRIPTOR int
	#define ERR_WOULDBLOCK EWOULDBLOCK
	#define ERR_CONNECTION_ABORTED ECONNABORTED


	#define ISVALIDSOCKET(s) ((s) >= 0)
	#define ISERROR(error) (errno == error)
	#define IFWOULDBLOCK() (WSAGetLastError() == ERR_WOULDBLOCK)
	#define SOCKET_CLOSE(fd) close(fd)
#endif

namespace WayMUD {
	bool NetworkInit();
	void NetworkShutdown();
	int NetworkGetLastError();
}