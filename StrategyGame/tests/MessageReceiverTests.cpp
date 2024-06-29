#include <gtest/gtest.h>
#include "messageReceiver/MessageReceiver.hpp"
#include "messageQueue/MessageQueue.hpp"
#include "zmq.hpp"
#include <memory>
#include "MessageQueueMock.hpp"


static const char* validAddress = "tcp://localhost:5555";
using ::testing::NaggyMock;
using ::testing::_;

class MessageReceiverTestsFixture : public testing::Test
{
protected:
	MessageReceiverTestsFixture() : zmqContext{}, senderSocket{ zmqContext ,zmq::socket_type::push }, sut{ validAddress, zmq::socket_type::pull, mockPtr }
	{
		senderSocket.connect(validAddress);
	}
	zmq::context_t zmqContext;
	zmq::socket_t senderSocket;
	std::shared_ptr<NaggyMock<MessageQueueMock>> mockPtr = std::make_shared<NaggyMock<MessageQueueMock>>();
	MessageReceiver sut;
};

TEST_F(MessageReceiverTestsFixture, willSaveMessageInQueueAfterReception)
{
	senderSocket.send(zmq::buffer("Hello"));
	EXPECT_CALL(*mockPtr, push_msg(_) ).Times(1);
}