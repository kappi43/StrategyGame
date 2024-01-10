#include "MessageReceiver.hpp"
#ifndef GLOG_NO_ABBREVIATED_SEVERITIES
#define GLOG_NO_ABBREVIATED_SEVERITIES
#endif
#include <glog/logging.h>
#include <string>
MessageQueue MessageReceiver::messageQueue{}; // static member definition
MessageReceiver::MessageReceiver(const std::string& address, zmq::socket_type socketType):
	zmqContext{},
	receiverSocket{zmqContext, socketType}
{
	LOG(INFO) << "Creating Receiver";
	connectSocket(address);
	receiverThread = std::thread{ &MessageReceiver::startReceiving, this };
}

void MessageReceiver::connectSocket(const std::string& address)
{
	try
	{
		LOG(INFO) << "Binding to: " << address;
		receiverSocket.bind(address);
	}
	catch (const zmq::error_t& error)
	{
		LOG(FATAL) << "MessageReceiver could not connect to " << address;
		throw error;
	}
}

void MessageReceiver::startReceiving()
{
		try
		{
			LOG(INFO) << "Receiving...";
			zmq::message_t msg{};
			receiverSocket.recv(msg);
			LOG(INFO) << "Received " << static_cast<const char*>(msg.data());
			messageQueue.push_msg(msg);
			gameEngine.init();
		}
		catch (const zmq::error_t& error)
		{
			LOG(FATAL) << "Exception on message reception";
			throw error;
		}
		try
		{
			receiverSocket.send(zmq::buffer("world"));
		}
		catch (const zmq::error_t& error)
		{
			LOG(FATAL) << "Exception on message send";
			throw error;
		}
}