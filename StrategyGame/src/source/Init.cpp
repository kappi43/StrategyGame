#include "Init.hpp"
#include "InitBoardReq.pb.h"
#include "EventMessageArrival.hpp"
#include "InitializeBoard.hpp"
#include "CloseEngineCommand.pb.h"
#include "ReqWrapper.pb.h"
Init::Init(my_context context) : my_base{ context }
{
	synchronize();
	LOG(INFO) << "Entering Init state";
	
}

void Init::synchronize()
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

boost::statechart::result Init::react(const EventMessageArrival& arrivingMessageEvent)
{
	auto& incomingMessage = arrivingMessageEvent.msg;
	LOG(INFO) << "Got message";
	GameEngine::InitBoardReq deserialized{};
	deserialized.ParseFromString(static_cast<const char*>(incomingMessage.data()));
	LOG(INFO) << "Sending resp";
	sendFromEngine(zmq::message_t{ std::to_string(deserialized.field_size()) });
	return transit<InitializeBoard>();
}

boost::statechart::result Init::react(const EventCloseEngine& arrivingMessageEvent)
{
	LOG(INFO) << "Got EventCloseEngine";
	outermost_context().shutdown();
	return terminate();
}