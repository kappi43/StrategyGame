#pragma once
#include "boost/statechart/state_machine.hpp"
#include <memory>
#include "messageQueue/IMessageGetter.h"
#include <zmq.hpp>
#include <thread>
#include <atomic>
#include <glog/logging.h>
#include <vector>
#include "CloseEngineCommandAck.pb.h"
class Init;
class GameEngineCore : public boost::statechart::state_machine<GameEngineCore, Init>
{
public:
	GameEngineCore(std::shared_ptr<IMessageGetter>, zmq::socket_type);
	std::optional<zmq::message_t> getMessage()
	{
		return messageGetter->get_msg();
	}
	zmq::send_result_t sendBack(zmq::message_t& msg)
	{
		return socket.send(msg, zmq::send_flags::none);
	}
	virtual ~GameEngineCore()
	{
		LOG(INFO) << "Joining";
		stateMachineThread.join();
	}
	void shutdown()
	{
		keep_running.store(false);
		GameEngine::CloseEngineCommandAck ack;
		sendBack(zmq::message_t{ ack.SerializeAsString() });
	}
	bool isRunning()
	{
		return keep_running;
	}
private:
	void init();
	zmq::context_t context;
	zmq::socket_t socket;
	std::atomic_bool keep_running;
	
	std::shared_ptr<IMessageGetter> messageGetter;
	std::thread stateMachineThread;
};