#pragma once
#include <queue>
#include "zmq.hpp"
#include <mutex>
#include "IMessagePusher.h"
#include "IMessageGetter.h"
class MessageQueue: public IMessagePusher, public IMessageGetter
{
public:
	MessageQueue();
	virtual void push_msg(const zmq::message_t& msg) override;
	virtual zmq::message_t get_msg() override;
private:
	std::queue<zmq::message_t> internalQueue;
	std::mutex messageQueueMutex;
};