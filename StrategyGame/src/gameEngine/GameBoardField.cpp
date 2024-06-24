#include "GameBoardField.h"
#include <glog/logging.h>
void GameBoardField::movePieceHere(std::unique_ptr<GamePiece> piece)
{
	//TODO complete this
	this->pieceOnThisField = std::move(piece);
}

void GameBoardField::moveOwnedPieceTo(GameBoardField& destination)
{
	if (this->pieceOnThisField)
	{
		destination.movePieceHere(std::move(this->pieceOnThisField));
	}
	else
	{
		LOG(WARNING) << "Tried to move a piece from a field that has no piece";
	}
}
