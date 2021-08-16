#ifndef UG_HOLE_PUNCH_COORDINATOR
#define UG_HOLE_PUNCH_COORDINATOR

#include <asio.hpp>
#include <thread>
#include <memory>
#include <map>
#include "client.hpp"
#include "room.hpp"

class HolePunchCoordinator {
public:
	HolePunchCoordinator();
	HolePunchCoordinator(int port);
	~HolePunchCoordinator() = default;

	void run();
	void stop();

private:
	void worker();

	void onConnectionAccepted(const std::error_code& ec);
	void onClientDesc(Client& client, bool success);

	void cleanEmptyRooms();

	int port;

	asio::io_service io_service;
	//asio::executor_work_guard<asio::io_service::executor_type> work_guard;
	std::thread worker_thread;

	asio::ip::tcp::acceptor acceptor;
	asio::ip::tcp::socket pendingSocket;

	std::map<Client *, std::shared_ptr<Client>> incomingClients;
	std::map<std::string, std::shared_ptr<Room>> rooms;
};

#endif //UG_HOLE_PUNCH_COORDINATOR
