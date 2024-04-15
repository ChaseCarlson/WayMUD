#pragma once

#if defined(_WIN32)
#include "winsock2.h"
#pragma comment(lib, "Ws2_32.lib")
#include <WS2tcpip.h>


#define SOCKET_DESCRIPTOR SOCKET
#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#define ISERROR(error) (WSAGetLastError() == error)
#define ERR_WOULDBLOCK WSAEWOULDBLOCK
#else
#define SOCKET_DESCRIPTOR int
#define ISVALIDSOCKET(s) ((s) >= 0)
#define ISERROR(error) (errno == error)
#define ERR_WOULDBLOCK EWOULDBLOCK
#endif

namespace WayMUD {
	bool NetworkInit();
	void NetworkShutdown();
}