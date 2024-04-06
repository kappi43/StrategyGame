#include <gtest/gtest.h>
#include "gameEngine/GameEngineCore.hpp"
#include "messageQueue/MessageQueue.hpp"
#include "zmq.hpp"
#include <memory>
#include "InitBoardReq.pb.h"
#include "ReqWrapper.pb.h"

static const char* validAdress = "tcp://localhost:5555";

class GameEngingeTestsFixture : public testing::Test
{
protected:
	GameEngingeTestsFixture() : zmqContext{}, senderSocket{ zmqContext ,zmq::socket_type::sub }
	{
		senderSocket.connect(validAdress);
		senderSocket.set(zmq::sockopt::subscribe, "");
		synchronize();
	}

	const void synchronize()
	{
		zmq::socket_t synchronizingSocket{ zmqContext, zmq::socket_type::req };
		synchronizingSocket.connect("tcp://localhost:5556");
		zmq::message_t rcv;
		while (true)
		{
			senderSocket.recv(rcv, zmq::recv_flags::dontwait);
			if (!rcv.empty())
			{
				synchronizingSocket.send(zmq::buffer("SYN ACK"));
				rcv = zmq::message_t{};
				synchronizingSocket.recv(rcv);
				break;
			}
		}
	}

	zmq::context_t zmqContext;
	zmq::socket_t senderSocket;
	std::shared_ptr<MessageQueue> msgQ = std::make_shared<MessageQueue>();
	GameEngineCore sut{ msgQ, zmq::socket_type::pub };
};

TEST_F(GameEngingeTestsFixture, EngineRepliesWithSizeOfProtoMessageArray)
{
	zmq::pollitem_t pollitems[] =
	{
		{ senderSocket, 0, ZMQ_POLLIN, 0 }
	};

	GameEngine::InitBoardReq initReq;
	initReq.add_field(1);
	initReq.add_field(2);
	initReq.add_field(3);
	zmq::message_t msg(initReq.SerializeAsString());
	msgQ->push_msg(msg);
	zmq::message_t received;
	while(true)
	{ 
		zmq::poll(pollitems, 1, std::chrono::milliseconds(0));
		if (pollitems[0].revents & ZMQ_POLLIN)
		{
			senderSocket.recv(received);
			break;
		}
	}
	ASSERT_EQ(received.to_string(), "3");
	GameEngine::ReqWrapper closeEngineCommand;
	closeEngineCommand.mutable_closeenginecommand();
	zmq::message_t msg2(closeEngineCommand.SerializeAsString());
	msgQ->push_msg(msg2);
}

TEST_F(GameEngingeTestsFixture, EngineShutsDownOnCloseEngineCommand)
{
	GameEngine::ReqWrapper closeEngineCommand;
	closeEngineCommand.mutable_closeenginecommand();
	zmq::message_t msg(closeEngineCommand.SerializeAsString());
	msgQ->push_msg(msg);
}
