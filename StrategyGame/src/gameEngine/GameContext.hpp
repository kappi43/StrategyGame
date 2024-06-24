#pragma once
#include <vector>
#include "GameBoardField.h"
namespace Rng {
	class RngDevice;
}
class GameContext
{
	void seed_board(const Rng::RngDevice&);
	std::vector<GameBoardField> board;
public:
	void setup_board(const int size);
	int getBoardSize() const
	{
		return board.size();
	}
};