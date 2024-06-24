#include <gtest/gtest.h>
#include "gameEngine/GameBoardField.h"
#include "gameEngine/GamePiece.h"
#include <memory>

class GameBoardFieldTestsFixture : public testing::Test
{
protected:
	GameBoardField sut;
};

TEST_F(GameBoardFieldTestsFixture, CanPutNewPiece)
{
	sut.movePieceHere(std::make_unique<GamePiece>());
	ASSERT_TRUE(sut.hasPiece());
}

TEST_F(GameBoardFieldTestsFixture, WillMoveExistingPiece)
{
	GameBoardField otherField;
	auto piecePtr = std::make_unique<GamePiece>();
	otherField.movePieceHere(std::move(piecePtr));
	otherField.moveOwnedPieceTo(sut);
	ASSERT_TRUE(sut.hasPiece());
	ASSERT_FALSE(otherField.hasPiece());
}
