#include "GameEngineCore.hpp"
#include "boost/statechart/simple_state.hpp"
#include "boost/statechart/transition.hpp"
#include "glog/logging.h"
GameEngineCore::GameEngineCore(std::shared_ptr<IMessageGetter> msgGetter) : messageGetter{msgGetter}
{}
void GameEngineCore::init()
{
	this->initiate();
}
class EventStart : public boost::statechart::event<EventStart> {};
class AwaitMessage;
class Init : public boost::statechart::simple_state<Init, GameEngineCore>
{
public:
	Init()
	{
		LOG(INFO) << "Entering Init state";
	}
	~Init()
	{
		LOG(INFO) << "Exiting Init state";
	}
	typedef boost::statechart::transition<EventStart, AwaitMessage> reactions;
};
class AwaitMessage : public boost::statechart::simple_state<AwaitMessage, GameEngineCore>
{
public:
	AwaitMessage()
	{
		LOG(INFO) << "Entering AwaitMessage state";
	}
	~AwaitMessage()
	{
		LOG(INFO) << "Exiting AwaitMessage state";
	}
};