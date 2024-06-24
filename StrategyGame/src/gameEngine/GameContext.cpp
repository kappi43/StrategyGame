#include "GameContext.hpp"
#include "Rng.hpp"
#include <glog/logging.h>

void GameContext::setup_board(const int size)
{
	LOG(INFO) << size << " SIZE";
	board.resize(size);
	seed_board(Rng::RngDevice{});
}

void GameContext::seed_board(const Rng::RngDevice& rng)
{
	//TODO
}
