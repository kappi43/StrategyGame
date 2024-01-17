#include <gtest/gtest.h>
#include "MessageReceiver.hpp"
#include "MessageQueue.hpp"
#include "zmq.hpp"
#include <memory>

const char* validAdress = "tcp://localhost:5555";

class MessageReceiverTestsFixture : public testing::Test
{
protected:
	MessageReceiverTestsFixture() : zmqContext{}, senderSocket{ zmqContext ,zmq::socket_type::req }, sut{ validAdress, zmq::socket_type::rep,msgQ ,gameEngine }
	{
		senderSocket.connect(validAdress);
	}
	zmq::context_t zmqContext;
	zmq::socket_t senderSocket;
	std::shared_ptr<MessageQueue> msgQ = std::make_shared<MessageQueue>();
	GameEngineCore gameEngine{ msgQ };
	MessageReceiver sut;
};

TEST_F(MessageReceiverTestsFixture, canSendMessage)
{
	senderSocket.send(zmq::buffer("Hello"));
	zmq::message_t received;
	senderSocket.recv(received);
	ASSERT_FALSE(received.empty());
}