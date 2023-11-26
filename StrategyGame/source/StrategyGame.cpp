#include <iostream>
#include "MessageReceiver.hpp"
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>

void initLogger()
{
	google::InitGoogleLogging("StrategyGame");
	FLAGS_logtostderr = 1;
}

int main(int argc, char* argv[])
{
	initLogger();
	MessageReceiver receiver("tcp://localhost:5555", zmq::socket_type::rep);
	return 0;
}

