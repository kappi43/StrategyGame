#pragma once
class GamePiece
{
public:
	int hp;
	int dmg;
	int movePoints;
	int attackDistance;
	GamePiece() :hp{ 3 }, dmg{ 1 }, movePoints{2}, attackDistance{1}
	{}
private:

};