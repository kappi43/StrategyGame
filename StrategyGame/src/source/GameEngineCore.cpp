#include "GameEngineCore.hpp"
#include "boost/statechart/state.hpp"
#include "glog/logging.h"
#include "InitBoardReq.pb.h"
GameEngineCore::GameEngineCore(std::shared_ptr<IMessageGetter> msgGetter, zmq::socket_type socketType) : messageGetter{msgGetter}, context{}, socket{context, socketType}
{
	socket.bind("tcp://*:5555");
	
	stateMachineThread = std::thread{ &GameEngineCore::init, this };
}

void GameEngineCore::init()
{
	this->initiate();
}
class Init : public boost::statechart::state<Init, GameEngineCore>
{
	std::optional<zmq::message_t> getMessageBlocking()
	{
		std::optional<zmq::message_t> msgOpt = outermost_context().getMessage();
		while (!msgOpt.has_value())
		{
			msgOpt = outermost_context().getMessage();
		}
		return msgOpt;
	}

	zmq::send_result_t sendFromEngine(zmq::message_t& msg)
	{
		return outermost_context().sendBack(msg);
	}

	void Synchronize()
	{
		zmq::context_t zmqContext;
		zmq::socket_t synchronizingSocket{ zmqContext, zmq::socket_type::rep };
		synchronizingSocket.bind("tcp://*:5556");
		LOG(INFO) << "Synchronizing to client";
		zmq::message_t msg;
		sendFromEngine(zmq::message_t{ "SYN" });
		synchronizingSocket.recv(msg);
		if (!msg.empty())
		{
			synchronizingSocket.send(zmq::buffer(""));
		}
	}

public:
	Init(my_context context) : my_base{context}
	{
		Synchronize();
		LOG(INFO) << "Entering Init state";
		auto& incomingMessage = getMessageBlocking();
		LOG(INFO) << "Got message";
		GameEngine::InitBoardReq deserialized{};
		deserialized.ParseFromString(static_cast<char*>(incomingMessage.value().data()));
		LOG(INFO) << "Sending resp";
		sendFromEngine(zmq::message_t{ std::to_string(deserialized.field_size()) });
	}
	~Init()
	{
		LOG(INFO) << "Exiting Init state";
	}
};