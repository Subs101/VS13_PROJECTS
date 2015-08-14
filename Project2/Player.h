#ifndef PLAYER_H_
#define PLAYER_H_
#include "LakeTile.h"
#include "Game.h"
#include <vector>
struct LakeTile;
struct Game;

struct Player
{

	Player();

	int takeTurn(Game& game);
	
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

	int setName(std::string name);
	std::string Player::getName();

	int setAI(bool flag);
	bool getAI();


	LakeTile topHand();
	LakeTile handTile(int handPos);

private:

	std::string playerName_;
	int numCoins_;
	std::vector<int> colorCards_;
	int points_;
	int orientation;
	std::vector<LakeTile> hand;
	bool AI_flag;

};




#endif