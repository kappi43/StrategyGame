#pragma once
#include <queue>
#include "zmq.hpp"
#include <mutex>
class MessageQueue
{
public:
	MessageQueue();
	void push_msg(const zmq::message_t& msg);
	zmq::message_t get_message();
private:
	std::queue<zmq::message_t> internalQueue;
	std::mutex messageQueueMutex;
};