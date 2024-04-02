#include "InitializeBoard.hpp"
#include "glog/logging.h"



InitializeBoard::InitializeBoard(my_context context) : my_base{ context }
{
	LOG(INFO) << "Initialize board state";
}

boost::statechart::result InitializeBoard::react(const EventMessageArrival& eventMessageArrival)
{
	LOG(INFO) << "Received message: ";
	LOG(INFO) << eventMessageArrival.msg.data();
	return terminate();
}

boost::statechart::result InitializeBoard::react(const EventCloseEngine&)
{
	LOG(INFO) << "Exiting";
	outermost_context().shutdown();
	return terminate();
}