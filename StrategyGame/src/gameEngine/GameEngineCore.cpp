
#include "GameEngineCore.hpp"
#include "boost/statechart/state.hpp"
#include <boost/statechart/event.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include "glog/logging.h"
#include "states/InitializeBoard.hpp"
#include "ReqWrapper.pb.h"
#include "states/Init.hpp"
#include <events/EventCloseEngine.hpp>
#include "events/EventMessageArrival.hpp"
#include "events/EventStartEngine.hpp"

GameEngineCore::GameEngineCore(std::shared_ptr<IMessageGetter> msgGetter, zmq::socket_type socketType) : messageGetter{ msgGetter }, context{}, socket{ context, socketType }, keep_running{ true }, gameContext{}
{
	socket.bind("tcp://*:5555");
	stateMachineThread = std::thread{ &GameEngineCore::init, this };
}

void GameEngineCore::init()
{
	this->initiate();
	while (keep_running)
	{
		std::optional<zmq::message_t> msg = this->getMessage();
		if (msg.has_value())
		{
			LOG(INFO) << "Processing message";
			GameEngine::ReqWrapper arrivingCommand{};
			if (!arrivingCommand.ParseFromString(msg->to_string()))
			{
				LOG(INFO) << "Couldn't parse message";
			}
			if (arrivingCommand.has_closeenginecommand())
			{
				LOG(INFO) << "Got close engine";
				this->process_event(EventCloseEngine());
			} 
			else if(arrivingCommand.has_initboardreq())
			{
				LOG(INFO) << "Got init board";
				this->process_event(EventMessageArrival(msg.value()));
			}
			else if (arrivingCommand.has_startengine())
			{
				LOG(INFO) << "Got start engine";
				this->process_event(EventStartEngine());
			}
		}
	}
	LOG(INFO) << "Exiting";
}