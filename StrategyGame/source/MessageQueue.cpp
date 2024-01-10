#include "MessageQueue.hpp"

MessageQueue::MessageQueue() : messageQueueMutex{}
{
}
void MessageQueue::push_msg(const zmq::message_t& msg)
{
	std::unique_lock<std::mutex> mutexGuard{ messageQueueMutex };
	internalQueue.push(zmq::message_t{msg.data(), msg.size()});
}
zmq::message_t MessageQueue::get_message()
{
	if (internalQueue.size() == 0)
	{
		return zmq::message_t{};
	}
	std::unique_lock<std::mutex> mutexGuard{ messageQueueMutex };
	zmq::message_t msg{};
	msg.move(internalQueue.front());
	internalQueue.pop();
	return msg;
}