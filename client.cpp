#include "client.hpp"

Client::Client(asio::ip::tcp::socket&& socket) : socket(std::move(socket)) {  }

void Client::readDescription(std::function<void(Client&, bool)> onComplete){
	using namespace std::placeholders;
	inMsg.async_readMsg(socket,
			std::bind(&Client::readNameComplete,
				this, std::ref(socket), onComplete, _1));
}

void Client::readNameComplete(asio::ip::tcp::socket& socket,
		std::function<void(Client&, bool)> onComplete,
		bool success)
{
	if(!success){
		onComplete(*this, false);
		return;
	}

	clientName = std::string(inMsg.getStr());
	using namespace std::placeholders;
	inMsg.async_readMsg(socket,
			std::bind(&Client::readRoomComplete,
				this, std::ref(socket), onComplete, _1));
}

void Client::readRoomComplete(asio::ip::tcp::socket& socket,
		std::function<void(Client&, bool)> onComplete,
		bool success)
{
	if(!success){
		onComplete(*this, false);
		return;
	}

	roomName = std::string(inMsg.getStr());
	using namespace std::placeholders;
	inMsg.async_readMsg(socket,
			std::bind(&Client::readDescComplete, this, onComplete, _1));
}

void Client::readDescComplete(
		std::function<void(Client&, bool)> onComplete,
		bool success)
{
	if(!success){
		onComplete(*this, false);
		return;
	}

	sdpDesc = std::string(inMsg.getStr());
	onComplete(*this, true);
}

void Client::readCandidate(std::function<void(Client&, bool)> onComplete){
	using namespace std::placeholders;
	inMsg.async_readMsg(socket,
			std::bind(&Client::readCandidateComplete,
				this, onComplete, _1));
}

void Client::readCandidateComplete(
		std::function<void(Client&, bool)> onComplete,
		bool success)
{
	if(!success){
		onComplete(*this, false);
		return;
	}

	candidates.emplace_back(inMsg.getStr());
	onComplete(*this, true);
}

void Client::sendMsg(std::string_view msg){
	if(!sendQueue.empty() || outMsg.isSendingNow()){
		sendQueue.emplace(msg);
		return;
	}

	outMsg.setStr(msg);
	using namespace std::placeholders;
	outMsg.async_sendMsg(socket, std::bind(&Client::onMsgSent, this, _1));
}

void Client::onMsgSent(bool success){
	if(!success){
		//TODO
	}

	if(sendQueue.empty())
		return;

	using namespace std::placeholders;
	outMsg.setStr(sendQueue.front());
	sendQueue.pop();
	outMsg.async_sendMsg(socket, std::bind(&Client::onMsgSent, this, _1));
}
