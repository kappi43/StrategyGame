#include <gtest/gtest.h>
#include "MessageReceiver.hpp"
#include "zmq.hpp"

const char* validAdress = "tcp://localhost:5555";
const char* invalidAdress = "invalid address";

class MessageReceiverTestsFixture : public testing::Test
{
protected:
	MessageReceiverTestsFixture() : zmqContext{}, senderSocket{ zmqContext ,zmq::socket_type::req }, sut{validAdress, zmq::socket_type::rep }
	{
		senderSocket.connect(validAdress);
	}
	zmq::context_t zmqContext;
	zmq::socket_t senderSocket;
	MessageReceiver sut;
};

TEST_F(MessageReceiverTestsFixture, canSendMessage)
{
	senderSocket.send(zmq::buffer("Hello"));
	zmq::message_t received;
	senderSocket.recv(received);
	ASSERT_FALSE(received.empty());
}

TEST_F(MessageReceiverTestsFixture, canSendMessage2)
{
	senderSocket.send(zmq::buffer("Hello"));
	zmq::message_t received;
	senderSocket.recv(received);
	ASSERT_FALSE(received.empty());
}