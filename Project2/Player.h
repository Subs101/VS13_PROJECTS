#ifndef PLAYER_H_
#define PLAYER_H_
#include "LakeTile.h"
#include "Game.h"
#include <vector>
struct LakeTile;

struct Player
{

	Player();
	int drawTile(std::vector<LakeTile>& lakeTiles_);
	int handSize();
	int popHand();
	int removeTile(int handPos);

	int incCoins();
	int decCoins();
	int getCoins();
	int incPoints(int n);

	int decColorHand(int color);
	int facing();
	int setFacing(int side);

	std::vector<int> getColorHand();
	int getPoints();

	int rotateTile(int handPos, int iterations);
	int drawColorCard(int color,std::vector<int>& deck);

	LakeTile topHand();
	LakeTile handTile(int handPos);

private:

	char* playerName_;
	int numCoins_;
	std::vector<int> colorCards_;
	int points_;
	int orientation;
	std::vector<LakeTile> hand;


};




#endif