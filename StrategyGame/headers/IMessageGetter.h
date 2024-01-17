#pragma once
#include "zmq.hpp"
class IMessageGetter
{
public:
	virtual zmq::message_t get_msg() = 0;
	virtual ~IMessageGetter() = default;
};

