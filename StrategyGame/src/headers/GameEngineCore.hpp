#pragma once
#include "boost/statechart/state_machine.hpp"
#include <memory>
#include "IMessageGetter.h"
#include <zmq.hpp>
#include <thread>
class Init;
class GameEngineCore : public boost::statechart::state_machine<GameEngineCore, Init>
{
public:
	GameEngineCore(std::shared_ptr<IMessageGetter>, zmq::socket_type);
	void init(); // wrapper for state_machine.initiate() to avoid undefined class error. 
	std::optional<zmq::message_t> getMessage()
	{
		return messageGetter->get_msg();
	}
	zmq::send_result_t sendBack(zmq::message_t& msg)
	{
		return socket.send(msg);
	}
	virtual ~GameEngineCore()
	{
		stateMachineThread.join();
	}
private:
	zmq::context_t context;
	zmq::socket_t socket;
	
	std::shared_ptr<IMessageGetter> messageGetter;
	std::thread stateMachineThread;
};