#ifndef UG_HOLE_PUNCH_ROOM_HPP
#define UG_HOLE_PUNCH_ROOM_HPP

#include <map>
#include <memory>
#include "client.hpp"

class Room{
public:
	Room(std::string name);

	void addClient(std::unique_ptr<Client>&& client);

	bool isFull() const { return clients.size() >= 2; }

private:
	void onClientCandidate(Client& client, bool success);

	std::string name;
	std::map<Client *, std::unique_ptr<Client>> clients;
};

#endif
