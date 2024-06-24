#pragma once
#include "GamePiece.h"
#include <memory>
#include <utility>
class GameBoardField
{
public:
	GameBoardField() : pieceOnThisField{nullptr} {}
	GameBoardField(const GameBoardField&) = delete;
	GameBoardField& operator = (const GameBoardField&) = delete;

	GameBoardField(GameBoardField&&) = default;
	GameBoardField& operator = (GameBoardField&&) = default;
	~GameBoardField(){}

	void movePieceHere(std::unique_ptr<GamePiece>);
	void moveOwnedPieceTo(GameBoardField&);
	inline bool hasPiece() const { return pieceOnThisField != nullptr; }
private:
	std::unique_ptr<GamePiece> pieceOnThisField;
};
