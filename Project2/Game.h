#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include "LakeTile.h"
#include "Player.h"
#define DEBUG 1

struct LakeTile;
struct Player;
struct Game
{
	Game(int players);

	void eventLoop();
	void drawGame();
	bool isGameOver();

	int initGame();
	int initLakeTiles();
	int initPointStacks();
	int placeTile(int row, int col);
	int getColorText(int color);
	int endTurn();

	int facingStartRED(LakeTile tile);


	int giveSynergy(int row,int col, LakeTile tile);
	int giveFacing(LakeTile tile);

	int buy(int stack);

	int showHandTiles();
	int showHandCards();

	int actionMenu();
	int strColorToInt(std::string);

	int shuffleTiles();
	int rng(int low, int high);
	

	bool isLocationAvailable(int row,int col);
	bool isTileConnected(int row,int col);



	//~Game();

private:

	int numPlayers; // 2-4
	int playedTiles;// 39 tiles total
	int whoseTurn;// 0 -3
	std::vector < std::vector<LakeTile> > gameBoard_;//main grid
	std::vector<LakeTile> lakeTiles_;//deck of laketiles
	std::vector <std::vector<int>>  occupied_;//shows which spots on gameboard are occupied
	std::vector<Player> players_;//player vectors
	std::vector<int> colorDeck_;
	std::vector <std::vector<int>> pointStacks_;






};







#endif