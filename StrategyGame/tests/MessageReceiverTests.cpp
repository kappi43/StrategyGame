#include <gtest/gtest.h>
#include "MessageReceiver.hpp"
#include "MessageQueue.hpp"
#include "zmq.hpp"
#include <memory>
#include "InitBoardReq.pb.h"

static const char* validAdress = "tcp://localhost:5555";

class MessageReceiverTestsFixture : public testing::Test
{
protected:
	MessageReceiverTestsFixture() : zmqContext{}, senderSocket{ zmqContext ,zmq::socket_type::req }, sut{ validAdress, zmq::socket_type::rep, msgQ}
	{
		senderSocket.connect(validAdress);
	}
	zmq::context_t zmqContext;
	zmq::socket_t senderSocket;
	std::shared_ptr<MessageQueue> msgQ = std::make_shared<MessageQueue>();
	GameEngineCore gameEngine{ msgQ, zmq::socket_type::rep };
	MessageReceiver sut;
};

//TEST_F(MessageReceiverTestsFixture, canSendSimpleMessage)
//{
//	senderSocket.send(zmq::buffer("Hello"));
//	ASSERT_FALSE(received.empty());
//}
//
//TEST_F(MessageReceiverTestsFixture, canSendProtoEncodedMessage)
//{
//	GameEngine::InitBoardReq initReq;
//	//========
//	initReq.add_field(1);
//	initReq.add_field(2);
//	initReq.add_field(3);
//	senderSocket.send(zmq::buffer(initReq.SerializeAsString()));
//}