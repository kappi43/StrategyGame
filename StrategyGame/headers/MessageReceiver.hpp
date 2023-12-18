#pragma once
#include "zmq.hpp"
#include <string>
#include <thread>
#include "GameEngineCore.hpp"
class MessageReceiver
{
public:
	MessageReceiver(const std::string&, zmq::socket_type);
	virtual ~MessageReceiver()
	{
		receiverThread.join();
	}

private:
	void connectSocket(const std::string&);
	void startReceiving();
	zmq::context_t zmqContext;
	zmq::socket_t receiverSocket;
	std::thread receiverThread;
	GameEngineCore gameEngine;
};

