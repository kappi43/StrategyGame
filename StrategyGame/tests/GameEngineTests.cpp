#include <gtest/gtest.h>
#include "gameEngine/GameEngineCore.hpp"
#include "messageQueue/MessageQueue.hpp"
#include "zmq.hpp"
#include <memory>
#include "InitBoardReq.pb.h"
#include "InitBoardResp.pb.h"
#include "ReqWrapper.pb.h"
#include <glog/logging.h>

static const char* validAddress = "tcp://localhost:5555";

class GameEngineTestsFixture : public testing::Test
{
protected:
	GameEngineTestsFixture() : zmqContext{}, senderSocket{ zmqContext ,zmq::socket_type::sub }
	{
		senderSocket.connect(validAddress);
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

	void startEngine()
	{
		GameEngine::ReqWrapper start;
		start.mutable_startengine();
		msgQ->push_msg(zmq::message_t{ start.SerializeAsString() });
	}

	void closeEngine()
	{
		GameEngine::ReqWrapper closeEngineCommand;
		closeEngineCommand.mutable_closeenginecommand();
		zmq::message_t msg(closeEngineCommand.SerializeAsString());
		msgQ->push_msg(msg);
	}

	void initializeGameEngineBoard()
	{
		GameEngine::ReqWrapper initReq;
		initReq.mutable_initboardreq()->add_field(1);
		initReq.mutable_initboardreq()->add_field(2);
		initReq.mutable_initboardreq()->add_field(3);
		zmq::message_t msg(initReq.SerializeAsString());
		msgQ->push_msg(msg);
	}

	zmq::message_t receiveMessageFromEngine()
	{
		zmq::message_t received;
		while (true)
		{
			zmq::poll(pollitems, 1, std::chrono::milliseconds(0));
			if (pollitems[0].revents & ZMQ_POLLIN)
			{
				if (!senderSocket.recv(received))
				{
					LOG(ERROR) << "Nothing received when expected!";
					return zmq::message_t{};
				}
				return received;
			}
		}
	}

	zmq::context_t zmqContext;
	zmq::socket_t senderSocket;
	std::shared_ptr<MessageQueue> msgQ = std::make_shared<MessageQueue>();
	GameEngineCore sut{ msgQ, zmq::socket_type::pub };
	const zmq::pollitem_t pollitems[1] =
	{
		{ senderSocket, 0, ZMQ_POLLIN, 0 }
	};
};

TEST_F(GameEngineTestsFixture, EngineInitializesBoard)
{
	startEngine();
	initializeGameEngineBoard();
	zmq::message_t received = receiveMessageFromEngine();
	GameEngine::InitBoardResp resp;
	resp.ParseFromString(received.to_string());
	ASSERT_EQ(resp.size(), 3);
}

TEST_F(GameEngineTestsFixture, EngineShutsDownOnCloseEngineCommand)
{
	closeEngine();
	receiveMessageFromEngine();
	ASSERT_FALSE(sut.isRunning());
}


