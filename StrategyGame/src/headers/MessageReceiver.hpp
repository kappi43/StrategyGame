#pragma once
#include "zmq.hpp"
#include <string>
#include <thread>
#include "GameEngineCore.hpp"
#include "IMessagePusher.h"
#include <memory>
class MessageReceiver
{
public:
	MessageReceiver(const std::string&, zmq::socket_type, std::shared_ptr<IMessagePusher>);
	virtual ~MessageReceiver()
	{
		receiverThread.join();
	}

private:
	std::shared_ptr<IMessagePusher> messagePusher;
	void connectSocket(const std::string&);
	void startReceiving();
	zmq::context_t zmqContext;
	zmq::socket_t receiverSocket;
	std::thread receiverThread;
};

