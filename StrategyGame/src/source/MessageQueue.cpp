#include "MessageQueue.hpp"
#include <iostream>


MessageQueue::MessageQueue() : messageQueueMutex{}
{
}
void MessageQueue::push_msg(const zmq::message_t& msg)
{
	
	std::unique_lock<std::mutex> mutexGuard{ messageQueueMutex };
	internalQueue.push(zmq::message_t{msg.data(), msg.size()});
}
std::optional<zmq::message_t> MessageQueue::get_msg()
{
	if (internalQueue.size() == 0)
	{
		return std::nullopt;
	}
	std::unique_lock<std::mutex> mutexGuard{ messageQueueMutex };
	zmq::message_t msg{};
	msg.move(internalQueue.front());
	internalQueue.pop();
	return msg;
}