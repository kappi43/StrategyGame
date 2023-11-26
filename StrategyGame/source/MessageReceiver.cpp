#include "MessageReceiver.hpp"
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>

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
		zmq::message_t msg;
		LOG(INFO) << "Receiving...";
		receiverSocket.recv(msg);
		LOG(INFO) << "Received " << msg.data();
		receiverSocket.send(zmq::buffer("world"));
 
}