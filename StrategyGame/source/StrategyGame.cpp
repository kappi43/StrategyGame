#include <iostream>
#include "MessageReceiver.hpp"
#ifndef GLOG_NO_ABBREVIATED_SEVERITIES
#define GLOG_NO_ABBREVIATED_SEVERITIES
#endif


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

