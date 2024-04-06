#include <gmock/gmock.h>
#include "messageQueue/MessageQueue.hpp"
#include <zmq.hpp>
#include <optional>

class MessageQueueMock : public MessageQueue
{
public:
	MOCK_METHOD(void, push_msg, (const zmq::message_t&), (override));
	MOCK_METHOD(std::optional<zmq::message_t>, get_msg, (), (override));
};