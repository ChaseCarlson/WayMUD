#include "Client.h"

WayMUD::Client::Client(std::shared_ptr<Socket> sock)
{
	this->socket = sock;
}