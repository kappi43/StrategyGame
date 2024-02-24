#include "GameEngineCore.hpp"
#include "boost/statechart/state.hpp"
#include "glog/logging.h"
#include "InitBoardReq.pb.h"
GameEngineCore::GameEngineCore(std::shared_ptr<IMessageGetter> msgGetter, zmq::socket_type socketType) : messageGetter{msgGetter}, context{}, socket{context, socketType}
{
	socket.connect("tcp://localhost:5555");
	this->init();
}

void GameEngineCore::init()
{
	this->initiate();
}
class EventStart : public boost::statechart::event<EventStart> {};
class Init : public boost::statechart::state<Init, GameEngineCore>
{
	std::optional<zmq::message_t>& getMessageBlocking()
	{
		std::optional<zmq::message_t> msgOpt = outermost_context().getMessage();
		while (!msgOpt.has_value())
		{
			msgOpt = outermost_context().getMessage();
		}
		return msgOpt;
	}
public:
	Init(my_context context) : my_base{context}
	{
		LOG(INFO) << "Entering Init state";
		auto& incomingMessage = getMessageBlocking();

		GameEngine::InitBoardReq deserialized{};
		deserialized.ParseFromString(static_cast<const char*>(incomingMessage.value().data()));
		LOG(INFO) << deserialized.field_size();
	}
	~Init()
	{
		LOG(INFO) << "Exiting Init state";
	}
};