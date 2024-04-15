// WayMUD.cpp : Defines the entry point for the application.
//

#include "WayMUD.h"
#include "network/Server.h"
//#include "server.h"

using namespace WayMUD;

int main()
{
	NetworkInit();
	Server* server = new Server(7777);
	server->Open();
	while (true)
	{
		server->Loop();
	}
	NetworkShutdown();
	return 0;
}
