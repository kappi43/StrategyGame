#include "InitializeBoard.hpp"
#include "ReqWrapper.pb.h"
#include "glog/logging.h"
#include "gameEngine/Rng.hpp"
#include "InitBoardResp.pb.h"

void InitializeBoard::setup_board(const GameEngine::ReqWrapper& msg)
{
	outermost_context().gameContext.setup_board(msg.initboardreq().field_size());
}
InitializeBoard::InitializeBoard(my_context context) : my_base{ context }
{
	LOG(INFO) << "Initialize board state";
}

boost::statechart::result InitializeBoard::react(const EventMessageArrival& eventMessageArrival)
{
	LOG(INFO) << "Received message ";
	GameEngine::ReqWrapper initBoard{};
	initBoard.ParseFromString(eventMessageArrival.msg.to_string());
	setup_board(initBoard);
	zmq::message_t msg{};
	if (outermost_context().sendBack(msg) == -1)
	{
		LOG(ERROR) << "Got -1 while sending back reply from engine:";
		LOG(ERROR) << std::strerror(errno);
	}
	LOG(INFO) << "Board setup. Terminating";
	outermost_context().shutdown();
	return terminate();
}

boost::statechart::result InitializeBoard::react(const EventCloseEngine&)
{
	LOG(INFO) << "Exiting";
	outermost_context().shutdown();
	return terminate();
}