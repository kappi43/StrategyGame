#pragma once
#include <queue>
#include "zmq.hpp"
#include <mutex>
#include "IMessagePusher.h"
#include "IMessageGetter.h"
#include <optional>
class MessageQueue: public IMessagePusher, public IMessageGetter
{
public:
	MessageQueue();
	virtual void push_msg(const zmq::message_t& msg) override;
	virtual std::optional<zmq::message_t> get_msg() override;
	virtual ~MessageQueue() = default;
private:
	std::queue<zmq::message_t> internalQueue;
	std::mutex messageQueueMutex;
};