
#include "GameEngineCore.hpp"
#include "boost/statechart/state.hpp"
#include <boost/statechart/event.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include "glog/logging.h"
#include "InitializeBoard.hpp"
#include "ReqWrapper.pb.h"
#include "Init.hpp"
#include <EventCloseEngine.hpp>
#include "EventMessageArrival.hpp"

GameEngineCore::GameEngineCore(std::shared_ptr<IMessageGetter> msgGetter, zmq::socket_type socketType) : messageGetter{msgGetter}, context{}, socket{context, socketType}, keep_running{true}
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
			arrivingCommand.ParseFromString(static_cast<const char*>(msg->data()));
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
		}
	}
	LOG(INFO) << "Exiting";
}