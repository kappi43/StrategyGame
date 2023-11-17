#pragma once
#include "zmq.hpp"

class MessageReceiver
{
public:
	MessageReceiver()
	{
	}

	~MessageReceiver()
	{
	}

private:
	zmq::socket_t receiverSocket;
};

