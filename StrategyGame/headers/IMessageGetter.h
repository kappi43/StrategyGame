#pragma once
#include "zmq.hpp"
#include <optional>
class IMessageGetter
{
public:
	virtual std::optional<zmq::message_t> get_msg() = 0;
	virtual ~IMessageGetter() = default;
};

