#pragma once
#include "Socket.h"
#include <memory>
#include <vector>
#include <string>

namespace WayMUD
{
	struct Client {
		std::shared_ptr<Socket> socket;
		std::string name;
	public:
		Client(std::shared_ptr<Socket> sock);
		std::shared_ptr<Socket> getSocket() { return socket; }
		std::string getName() { return name; }
		void setName(std::string name) { this->name = name; }
	};
}
