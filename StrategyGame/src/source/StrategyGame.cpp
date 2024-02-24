#include <iostream>
#include "MessageReceiver.hpp"
#ifndef GLOG_NO_ABBREVIATED_SEVERITIES
#define GLOG_NO_ABBREVIATED_SEVERITIES
#endif
#include <glog/logging.h>
#include <MessageQueue.hpp>
#include <GameEngineCore.hpp>
#include <memory>
void initLogger()
{
	google::InitGoogleLogging("StrategyGame");
	FLAGS_logtostderr = 1;
}

int main(int argc, char* argv[])
{
	initLogger();

	std::shared_ptr<MessageQueue> msgQueue = std::make_shared<MessageQueue>();
	GameEngineCore gameEngine{ msgQueue, zmq::socket_type::pub };

	MessageReceiver receiver("tcp://localhost:5555", zmq::socket_type::rep, msgQueue);
	return 0;
}