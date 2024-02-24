#pragma once
#include "zmq.hpp"
class IMessagePusher
{
public:
	virtual void push_msg(const zmq::message_t&) = 0;
	virtual ~IMessagePusher() = default;
};
