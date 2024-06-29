#include "states/Init.hpp"
#include "events/EventMessageArrival.hpp"
#include "events/EventStartEngine.hpp"
#include "states/InitializeBoard.hpp"
#include "InitBoardReq.pb.h"
#include "CloseEngineCommand.pb.h"
#include "ReqWrapper.pb.h"
#include <cerrno>
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
	if (!synchronizingSocket.recv(msg))
	{
		LOG(ERROR) << "Error while synchronizing engine with peers";
	}
	if (!msg.empty())
	{
		if (synchronizingSocket.send(zmq::buffer("")) == -1)
		{
			LOG(ERROR) << "Got -1 while sending back syn message from engine:";
			LOG(ERROR) << std::strerror(errno);
		}
	}
}

boost::statechart::result Init::react(const EventMessageArrival& arrivingMessageEvent)
{
	auto& incomingMessage = arrivingMessageEvent.msg;
	LOG(INFO) << "Got message";
	GameEngine::ReqWrapper deserialized{};
	deserialized.ParseFromString(static_cast<const char*>(incomingMessage.data()));
	if (deserialized.has_startengine())
	{
		LOG(INFO) << "Configuring engine";
	}
	return transit<InitializeBoard>();
}

boost::statechart::result Init::react(const EventCloseEngine& arrivingMessageEvent)
{
	LOG(INFO) << "Got EventCloseEngine";
	outermost_context().shutdown();
	return terminate();
}
boost::statechart::result Init::react(const EventStartEngine& arrivingMessageEvent)
{
	LOG(INFO) << "Got EventStartEngine";
	return transit<InitializeBoard>();
}