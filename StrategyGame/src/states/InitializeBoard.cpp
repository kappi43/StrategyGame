#include "InitializeBoard.hpp"
#include "InitBoardReq.pb.h"
#include "glog/logging.h"
#include "gameEngine/Rng.hpp"
#include "InitBoardResp.pb.h"

void InitializeBoard::setup_board(const GameEngine::InitBoardReq& msg)
{
	board.resize(msg.field_size());
	seed_board(Rng::RngDevice{});
	GameEngine::InitBoardResp resp{};
	resp.set_size(board.size()); // cast from size_t to int32!
	for (auto var : board)
	{
		resp.add_fieldvalues(var);
	}
    zmq::message_t respMsg{resp.SerializeAsString()};
	outermost_context().sendBack(respMsg);
}

void InitializeBoard::seed_board(const Rng::RngDevice& rng)
{
	for (int i = 0; i < board.size(); ++i)
	{
		board[i] = rng.getRandomInt(1, 10);
	}
}

InitializeBoard::InitializeBoard(my_context context) : my_base{ context }
{
	LOG(INFO) << "Initialize board state";
}

boost::statechart::result InitializeBoard::react(const EventMessageArrival& eventMessageArrival)
{
	LOG(INFO) << "Received message ";
	GameEngine::InitBoardReq initBoard{};
	initBoard.ParseFromString(eventMessageArrival.msg.to_string());
	setup_board(initBoard);
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