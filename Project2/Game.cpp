#include <iostream>
#include "Game.h"
#include "LakeTile.h"
#include <windows.h> // WinApi header
#include "Player.h"
#include <string>
#include <cstdio>
namespace
{
	const int twoPlayerMAXTILES = 16;
	const int threePlayerMAXTILES = 18;
	const int fourPlayerMAXTILES = 20;

	int gameboard_cols = 10;
	int gameboard_rows = 10;

	int startPiece_row = 5;
	int startPiece_col = 5;
}

Game::Game(int players)
{
	numPlayers = players;

	while (true)
	{
		//welcome screen
		

		eventLoop();

		//ask if play again
		//if true with how many player?

	}

	


}

bool Game::isGameOver()
{
	switch (numPlayers)
	{
	case 2:
		if (playedTiles >= twoPlayerMAXTILES + numPlayers*3)
		{
			return true;
		}
		else
		{
			return false;
		}
	case 3:
		if (playedTiles >= threePlayerMAXTILES + numPlayers*3)
		{
			return true;
		}
		else
		{
			return false;
		}
	case 4:
		if (playedTiles >= fourPlayerMAXTILES + numPlayers*3)
		{
			return true;
		}
		else
		{
			return false;
		}
	default: break;
	}
	return false;
}

void Game::eventLoop()
{
	
	//initialize game
	initGame();
		//shuffle game tiles/ deal 3 game tiles to each player


	//get player names



	//while loop taking turns until game is over
		//game is over when no tiles in all players hand
	while (!isGameOver())
	{
		
		
		//phase 1 exchange card input
		//phase 2 buy victory points
		//phase 3 place tile

		while(actionMenu() > 0);
		
	
		
		//phase 4 end turn and draw tile
		endTurn();

		drawGame();
		showHandCards();

	}


}
int Game::strColorToInt(std::string s)
{

	if (s == "R")
	{
		return RED;
	}
	else if (s == "B")
	{
		return BLUE;
	}
	else if (s == "BL")
	{
		return BLACK;
	}
	else if (s == "P")
	{
		return PINK;
	}
	else if (s == "G")
	{
		return GREEN;
	}
	else if (s == "W")
	{
		return WHITE;
	}
	else if (s == "O")
	{
		return ORANGE;
	}
}

int Game::buy(int stack)
{
	int color;
	std::string strColor1;



	switch (stack)
	{
	case 1:
		//4 of a kind
		std::cout << "Which color are you buying with?\n";
		std::cin >> strColor1;

		color = strColorToInt(strColor1);

		players_[whoseTurn].incPoints(pointStacks_[0].back());
		pointStacks_[0].pop_back();

		if (players_[whoseTurn].getColorHand()[color] < 4)
		{
			std::cout << "Invalid Buy: Don't have 4 of that color.\n";
			return -1;
		}

		for (int i = 0; i < 4; i++)
		{
			players_[whoseTurn].decColorHand(color);
			colorDeck_[color]++;
		}
		

		return 0;

		break;
	case 2:

		//2 of 3 color
		players_[whoseTurn].incPoints(pointStacks_[1].back());
		pointStacks_[1].pop_back();
		return 0;
		break;
	case 3:
		//1 of each color
		for (int i = 0; i < 7; i++)
		{
			if (players_[whoseTurn].getColorHand()[i] < 1)
			{
				std::cout << "Invalid Buy: Don't have one of each color.\n";
				return -1;
			}
		}

		for (int i = 0; i < 7; i++)
		{
			//dec each color in hand
			players_[whoseTurn].decColorHand(i);

			//inc each color in color deck
			colorDeck_[i]++;
		}


			players_[whoseTurn].incPoints(pointStacks_[2].back());
			pointStacks_[2].pop_back();
			return 0;
			break;
		default:break;
		}
	



	return 0;
}

int Game::actionMenu()
{
	std::string command;
	int choice1, choice2;
	std::string schoice1, schoice2;

	std::cout << "Give command\n";
	std::cin >> command;


	if (command == "buy")
	{
		do
		{

			while (!(std::cin >> choice1))
			{
				std::cin.clear();
				std::cin.ignore();
			}

		} while (buy(choice1) < 0);

		return 1;



	}
	else if (command == "show")
	{
		std::cin >> schoice1;

		if (schoice1 == "hand")
		{
			std::cin >> schoice2;

			if (schoice2 == "tiles")
			{
				showHandTiles();
				return 1;
			}
			else if (schoice2 == "cards")
			{
				showHandCards();
				return 1;
			}
			else
			{
				std::cout << "Bad input\n";
				return 1;
			}

		}
		else if (schoice1 == "game")
		{
			drawGame();
			return 1;
		}
		else
		{
			std::cout << "Bad input\n";
			return 1;
		}
		
		
		return 1;

	}
	else if (command == "exchange")
	{


		do
		{

			while (!(std::cin >> schoice1 >> schoice2))
			{
				std::cin.clear();
				std::cin.ignore();
			}

		} while (/*exchange(choice1, choice2) < 0*/1);


		return 1;
	}
	else if (command == "placetile")
	{
		
		do
		{
		
			while (!(std::cin >> choice1>>choice2))
			{
				std::cin.clear();
				std::cin.ignore();
			}

		} while (placeTile(choice1, choice2) < 0);

		return 0;//end action loop
	}

	std::cout << "Invalid command\n";

	return 1;
}

int Game::placeTile(int row, int col)
{
	if ( row < 0 || col < 0 ||
		row >= gameboard_rows || col>= gameboard_cols || !isLocationAvailable(row, col) || !isTileConnected(row, col)
		)
	{
		if (DEBUG)
		{
			std::cout << "invalid location to place tile\n";
		}

		return -1;

	}

	//give player synergy cards & coin if applicable
	giveSynergy(row,col,players_[whoseTurn].topHand());

	giveFacing(players_[whoseTurn].topHand());

	gameBoard_[row][col] = players_[whoseTurn].topHand();

	players_[whoseTurn].popHand();//remove tile from players hand

	playedTiles++;

	occupied_[row][col] = 1;

	
	

	//give players card color that faces them on placed tile.

	return 0;

}


int Game::giveFacing(LakeTile tile)
{
	int i = 0;
	int j = whoseTurn;

	while (i < numPlayers)
	{
		players_[j].drawColorCard(tile.getTileColors()[players_[j].facing()],colorDeck_);

		if (j == numPlayers - 1)
		{
			j = 0;
		}
		else
		{
			j++;
		}

		i++;
	}
	return 0;

}

int Game::giveSynergy(int row,int col,LakeTile tile)
{
	//check each direction for synergy and give player that color bonus
	bool synergyFlag = false;
	//top
	if (row - 1 > 0)
	{
		if (tile.getTileColors()[TOP] == gameBoard_[row - 1][col].getTileColors()[BOT]
			&& occupied_[row - 1][col])
		{
			players_[whoseTurn].drawColorCard(tile.getTileColors()[TOP], colorDeck_);
			synergyFlag = true;
		}
	}
	
	//right

	if (col + 1 < gameboard_cols)
	{
		if (tile.getTileColors()[RIGHT] == gameBoard_[row][col + 1].getTileColors()[LEFT]
			&& occupied_[row][col + 1])
		{
			players_[whoseTurn].drawColorCard(tile.getTileColors()[RIGHT], colorDeck_);
			synergyFlag = true;
		}
	}
	
	//bot
	if (row + 1 < gameboard_rows)
	{
		if (tile.getTileColors()[BOT] == gameBoard_[row + 1][col].getTileColors()[TOP]
			&& occupied_[row + 1][col])
		{
			players_[whoseTurn].drawColorCard(tile.getTileColors()[BOT], colorDeck_);
			synergyFlag = true;
		}

	}

	
	//left

	if (col - 1 > 0)
	{
		if (tile.getTileColors()[LEFT] == gameBoard_[row][col - 1].getTileColors()[RIGHT]
			&& occupied_[row][col - 1])
		{
			players_[whoseTurn].drawColorCard(tile.getTileColors()[LEFT], colorDeck_);
			synergyFlag = true;
		}
	}



	//animal token present?
	if (tile.hasAnimalToken() && synergyFlag == true)
	{
		players_[whoseTurn].incCoins();
	}
	return 0;

}

int Game::initLakeTiles()
{
	//create all tiles

	lakeTiles_.push_back(LakeTile(ORANGE, BLACK, RED, RED, false));
	lakeTiles_.push_back(LakeTile(BLUE, BLACK, ORANGE, GREEN, false));
	lakeTiles_.push_back(LakeTile(BLACK, PINK, RED, BLACK, true));

	lakeTiles_.push_back(LakeTile(GREEN,PINK,BLUE,WHITE, false));
	lakeTiles_.push_back(LakeTile(GREEN,PINK,RED,PINK,true));
	lakeTiles_.push_back(LakeTile(WHITE,BLACK,WHITE,BLACK, true));

	lakeTiles_.push_back(LakeTile(GREEN,GREEN,RED,GREEN,false));
	lakeTiles_.push_back(LakeTile(RED,GREEN,GREEN,RED,true));
	lakeTiles_.push_back(LakeTile(WHITE,BLACK,BLUE,RED,false));

	lakeTiles_.push_back(LakeTile(BLUE,BLACK,WHITE,GREEN, false));
	lakeTiles_.push_back(LakeTile(ORANGE,WHITE,GREEN,RED,false));
	lakeTiles_.push_back(LakeTile(ORANGE,BLUE,GREEN,BLUE, false));

	lakeTiles_.push_back(LakeTile(ORANGE,PINK,WHITE,RED, false));
	lakeTiles_.push_back(LakeTile(GREEN,PINK,RED,BLACK, false));
	lakeTiles_.push_back(LakeTile(GREEN,ORANGE,GREEN,WHITE, true));

	lakeTiles_.push_back(LakeTile(ORANGE,BLUE,WHITE,ORANGE,true));
	lakeTiles_.push_back(LakeTile(GREEN,PINK,BLUE,WHITE,false));
	lakeTiles_.push_back(LakeTile(PINK,PINK,BLACK,PINK,false));

	lakeTiles_.push_back(LakeTile(ORANGE,PINK,BLACK,WHITE,false));
	lakeTiles_.push_back(LakeTile(ORANGE,BLUE,PINK,BLACK,false));
	lakeTiles_.push_back(LakeTile(PINK,RED,GREEN,PINK,true));
	
	lakeTiles_.push_back(LakeTile(ORANGE,BLACK,PINK,RED,false));
	lakeTiles_.push_back(LakeTile(WHITE,WHITE,ORANGE,PINK,true));
	lakeTiles_.push_back(LakeTile(BLUE,PINK,WHITE,RED,false));

	lakeTiles_.push_back(LakeTile(RED,GREEN,WHITE,WHITE, false));
	lakeTiles_.push_back(LakeTile(RED, BLACK, GREEN, BLUE, false));
	lakeTiles_.push_back(LakeTile(BLACK,BLACK,ORANGE,WHITE,true));

	lakeTiles_.push_back(LakeTile(RED,ORANGE,RED,BLACK,true));
	lakeTiles_.push_back(LakeTile(GREEN,PINK,BLUE,PINK,true));
	lakeTiles_.push_back(LakeTile(BLUE,BLACK,BLUE,WHITE,true));

	lakeTiles_.push_back(LakeTile(RED,WHITE,BLACK,ORANGE,false));
	lakeTiles_.push_back(LakeTile(BLACK,PINK,BLUE,BLUE,false));
	lakeTiles_.push_back(LakeTile(BLUE,BLUE,BLACK,BLUE,true));

	lakeTiles_.push_back(LakeTile(WHITE,ORANGE,RED,BLUE,false));
	lakeTiles_.push_back(LakeTile(RED,ORANGE,RED,WHITE,true));
	lakeTiles_.push_back(LakeTile(PINK,ORANGE,ORANGE,ORANGE,false));

	lakeTiles_.push_back(LakeTile(BLUE,PINK,RED,GREEN,false));
	lakeTiles_.push_back(LakeTile(WHITE,BLACK,ORANGE,BLACK,false));
	lakeTiles_.push_back(LakeTile(BLUE,ORANGE,BLUE,ORANGE,true));

	shuffleTiles();

	switch (numPlayers)
	{
	case 2:
	{
	    //assign and pop 3 * players off the lakeTile stack
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				players_[i].drawTile(lakeTiles_);
			}
			
		}

		while (lakeTiles_.size() > twoPlayerMAXTILES)
		{
			lakeTiles_.pop_back();
		}
		return 0;

	case 3:
	{
		 //assign and pop 3 * players off the lakeTile stack
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				players_[i].drawTile(lakeTiles_);
			}
			
		}

		while (lakeTiles_.size() > threePlayerMAXTILES)
		{
			lakeTiles_.pop_back();
		}
		return 0;
	}
	case 4:
	{
			  //assign and pop 3 * players off the lakeTile stack
			  for (int i = 0; i < 4; i++)
			  {
				  for (int j = 0; j < 3; j++)
				  {
					  players_[i].drawTile(lakeTiles_);
				  }

			  }

			  while (lakeTiles_.size() > fourPlayerMAXTILES)
			  {
				  lakeTiles_.pop_back();
			  }
			  return 0;
	}
		

	}
	}
	return -1;

}


int Game::initGame()
{
	int numColorCards;
	


	players_ = std::vector<Player>(numPlayers, Player());

	switch (numPlayers)
	{
	case 2:
		numColorCards = 5;
		players_[0].setFacing(TOP);
		players_[1].setFacing(RIGHT);
		break;
	case 3:
		numColorCards = 7;
		players_[0].setFacing(TOP);
		players_[1].setFacing(RIGHT);
		players_[2].setFacing(BOT);
		break;
	case 4:
		numColorCards = 8;
		players_[0].setFacing(TOP);
		players_[1].setFacing(RIGHT);
		players_[2].setFacing(BOT);
		players_[3].setFacing(LEFT);
		break;
	default: break;
	}


	colorDeck_ = std::vector<int>(ORANGE + 1, numColorCards);


	gameBoard_ = std::vector<std::vector<LakeTile> >(
		gameboard_rows, std::vector<LakeTile>(gameboard_cols, LakeTile()));

	occupied_ = std::vector<std::vector<int> >(
		gameboard_rows, std::vector<int>(gameboard_cols, 0));

	//starting piece in middle [5][5]
	occupied_[startPiece_row][startPiece_col] = 1;
	gameBoard_[startPiece_row][startPiece_col].setTile(BLUE,RED,WHITE,BLACK, false);
	

	whoseTurn = facingStartRED(gameBoard_[startPiece_row][startPiece_col]);

	playedTiles = 0;
	giveFacing(gameBoard_[startPiece_row][startPiece_col]);

	initLakeTiles();//deck in lakeTiles_ and players hand delt
	initPointStacks();

	return 0;
}

int Game::initPointStacks()
{

	pointStacks_ = std::vector<std::vector<int> >(
		3, std::vector<int>(0, 0));
	switch (numPlayers)
	{
	case 2:
		pointStacks_[0].push_back(4);
		pointStacks_[0].push_back(5);
		pointStacks_[0].push_back(5);
		pointStacks_[0].push_back(6);
		pointStacks_[0].push_back(7);
		pointStacks_[0].push_back(8);


		pointStacks_[1].push_back(5);
		pointStacks_[1].push_back(5);
		pointStacks_[1].push_back(6);
		pointStacks_[1].push_back(7);
		pointStacks_[1].push_back(8);
		pointStacks_[1].push_back(9);

		pointStacks_[2].push_back(5);
		pointStacks_[2].push_back(6);
		pointStacks_[2].push_back(7);
		pointStacks_[2].push_back(8);
		pointStacks_[2].push_back(9);
		pointStacks_[2].push_back(10);
		
		break;
	case 3:
		pointStacks_[0].push_back(4);
		pointStacks_[0].push_back(5);
		pointStacks_[0].push_back(5);
		pointStacks_[0].push_back(5);
		pointStacks_[0].push_back(6);
		pointStacks_[0].push_back(6);
		pointStacks_[0].push_back(7);
		pointStacks_[0].push_back(8);


		pointStacks_[1].push_back(5);
		pointStacks_[1].push_back(5);
		pointStacks_[1].push_back(6);
		pointStacks_[1].push_back(6);
		pointStacks_[1].push_back(7);
		pointStacks_[1].push_back(7);
		pointStacks_[1].push_back(8);
		pointStacks_[1].push_back(9);


		pointStacks_[2].push_back(5);
		pointStacks_[2].push_back(6);
		pointStacks_[2].push_back(6);
		pointStacks_[2].push_back(7);
		pointStacks_[2].push_back(7);
		pointStacks_[2].push_back(8);
		pointStacks_[2].push_back(8);
		pointStacks_[2].push_back(9);
		pointStacks_[2].push_back(10);


		break;
	case 4:
		pointStacks_[0].push_back(4);
		pointStacks_[0].push_back(5);
		pointStacks_[0].push_back(5);
		pointStacks_[0].push_back(5);
		pointStacks_[0].push_back(6);
		pointStacks_[0].push_back(6);
		pointStacks_[0].push_back(7);
		pointStacks_[0].push_back(7);
		pointStacks_[0].push_back(8);

		pointStacks_[1].push_back(5);
		pointStacks_[1].push_back(5);
		pointStacks_[1].push_back(6);
		pointStacks_[1].push_back(6);
		pointStacks_[1].push_back(7);
		pointStacks_[1].push_back(7);
		pointStacks_[1].push_back(8);
		pointStacks_[1].push_back(8);
		pointStacks_[1].push_back(9);

		pointStacks_[2].push_back(5);
		pointStacks_[2].push_back(6);
		pointStacks_[2].push_back(6);
		pointStacks_[2].push_back(7);
		pointStacks_[2].push_back(7);
		pointStacks_[2].push_back(8);
		pointStacks_[2].push_back(8);
		pointStacks_[2].push_back(9);
		pointStacks_[2].push_back(9);
		pointStacks_[2].push_back(10);
		break;
	default: break;
	}



	return 0;
}

int Game::facingStartRED(LakeTile tile)
{

	bool facingRed = false;
	std::srand(1);

	for (int i = 0; i < numPlayers; i++)
	{
		if (gameBoard_[startPiece_row][startPiece_col].getTileColors()[players_[i].facing()] == RED)
		{
			facingRed = true;
			return i;
		}
	}
	
	if (facingRed == false)
	{
	
		return rng(0, numPlayers - 1);
	}

}

bool Game::isLocationAvailable(int row, int col)
{
	if (row < 0 || row >= gameboard_rows || col < 0 || col >= gameboard_cols)
	{
		return true;
	}

	if (occupied_[row][col] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Game::isTileConnected(int row, int col)
{
	int degreeConnected = 0;

	if (row < 0 || row >= gameboard_rows || col < 0 || col >= gameboard_cols)
	{
		return false;
	}


	if (row + 1 < gameboard_cols)
	{
		degreeConnected += occupied_[row + 1][col];
	}
	if (row - 1 > 0)
	{
		degreeConnected += occupied_[row - 1][col];
	}
	if (col + 1 < gameboard_rows)
	{
		degreeConnected += occupied_[row][col + 1];
	}
	if (col - 1 > 0)
	{
		degreeConnected += occupied_[row][col - 1];
	}

	if (degreeConnected >= 1)
	{
		return true;
	}
	else
	{
		return false;
	}


}

void Game::drawGame()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	

	std::cout << "-------------------------------------\n";
	for (int i = 0; i < gameboard_cols; i++)
	{
		for (int j = 0; j < gameboard_rows; j++)
		{
		
			if (occupied_[i][j])
			{
				SetConsoleTextAttribute(hConsole,
					getColorText(gameBoard_[i][j].getTileColors()[TOP]));
				std::cout <<" # ";
				SetConsoleTextAttribute(hConsole, getColorText(-1));
				std::cout << "";

				
			}
			else
			{
				std::cout << "   ";
			}
			

		}
		std::cout << "\n";

		for (int j = 0; j < gameboard_rows; j++)
		{

			if (occupied_[i][j])
			{
				SetConsoleTextAttribute(hConsole,
					getColorText(gameBoard_[i][j].getTileColors()[LEFT]));
				std::cout << "#";
				SetConsoleTextAttribute(hConsole, getColorText(-1));
				if (gameBoard_[i][j].hasAnimalToken())
				{
					std::cout << "*";
				}
				else
				{
					std::cout << " ";
				}
				
				SetConsoleTextAttribute(hConsole,
					getColorText(gameBoard_[i][j].getTileColors()[RIGHT]));
				std::cout << "#";
				SetConsoleTextAttribute(hConsole, getColorText(-1));
				
			}
			else
			{
				std::cout << "   ";
			}
		}
		std::cout << "\n";

		for (int j = 0; j < gameboard_rows; j++)
		{
			if (occupied_[i][j])
			{
				SetConsoleTextAttribute(hConsole,
					getColorText(gameBoard_[i][j].getTileColors()[BOT]));
				std::cout << " # ";
				SetConsoleTextAttribute(hConsole, getColorText(-1));
				
			}
			else
			{
				std::cout << "   ";
			}

		}
		std::cout << "\n";



	}
	std::cout << "-------------------------------------\n";


}

int Game::showHandCards()
{

	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << " ____________________\n";


	std::cout << " |";
	SetConsoleTextAttribute(hConsole,
		getColorText(RED));
	std::cout << "R  ";
	SetConsoleTextAttribute(hConsole, getColorText(-1));
	
	SetConsoleTextAttribute(hConsole,
		getColorText(BLUE));
	std::cout << "B  ";
	SetConsoleTextAttribute(hConsole, getColorText(-1));

	SetConsoleTextAttribute(hConsole,
		getColorText(GREEN));
	std::cout << "G  ";
	SetConsoleTextAttribute(hConsole, getColorText(-1));


	SetConsoleTextAttribute(hConsole,
		getColorText(BLACK));
	std::cout << "BL ";
	SetConsoleTextAttribute(hConsole, getColorText(-1));

	SetConsoleTextAttribute(hConsole,
		getColorText(ORANGE));
	std::cout << "O  ";
	SetConsoleTextAttribute(hConsole, getColorText(-1));


	SetConsoleTextAttribute(hConsole,
		getColorText(WHITE));
	std::cout << "W  ";
	SetConsoleTextAttribute(hConsole, getColorText(-1));

	SetConsoleTextAttribute(hConsole,
		getColorText(PINK));
	std::cout << "P";
	SetConsoleTextAttribute(hConsole, getColorText(-1));

	std::cout << "|";

	std::cout << " Coins  Points";

	std::cout << "\n";



	


	std::cout <<" |"<< players_[whoseTurn].getColorHand()[RED] << "  ";
	std::cout << players_[whoseTurn].getColorHand()[BLUE] << "  ";
	std::cout << players_[whoseTurn].getColorHand()[GREEN] << "  ";
	std::cout << players_[whoseTurn].getColorHand()[BLACK] << "  ";
	std::cout << players_[whoseTurn].getColorHand()[ORANGE] << "  ";
	std::cout << players_[whoseTurn].getColorHand()[WHITE] << "  ";
	std::cout << players_[whoseTurn].getColorHand()[PINK];
	std::cout << "| "<<players_[whoseTurn].getCoins()<<"      "<<players_[whoseTurn].getPoints()<<"\n";

	std::cout << " --------------------\n";
	return 0;
}

int Game::getColorText(int color)
{
	switch (color)
	{
	case RED:
		return 4;
	case BLACK:
		return 8;
	case BLUE:
		return 9;
	case GREEN:
		return 2;
	case ORANGE:
		return 6;
	case WHITE:
		return 0xF;
	case PINK:
		return 5;
	default:
		return 7;
	}

}

int Game::shuffleTiles()
{
	int r;
	std::srand(1);
	LakeTile temp;
	LakeTile temp2;

	for (int i = 0; i < lakeTiles_.size(); i++)
	{
		r = rng(0, lakeTiles_.size()- 1);
	
		temp = lakeTiles_[i];
		temp2 = lakeTiles_[r];

		lakeTiles_[i] = temp2;
		lakeTiles_[r] = temp;


	}

		
	return 0;

}

int Game::rng(int low, int high)
{
	int n;
	while (1){

		n = floor(rand() % (high + 1));
		if (n >= low && n <= high)
		{
			break;
		}
	}

	return n;
}

int Game::endTurn()
{
	players_[whoseTurn].drawTile(lakeTiles_);
	std::cout << "lake tiles remaining: " << lakeTiles_.size()<<"\n";
	std::cout << "played tiles: " << playedTiles << "\n";
	if (whoseTurn == numPlayers - 1)//restart back to player 0
	{
		whoseTurn = 0;
	}
	else
	{
		whoseTurn++;
	}
	
	std::cout << "player " << whoseTurn << "'s turn.\n";
	return 0;

}

int Game::showHandTiles()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int j = players_[whoseTurn].handSize();


	if (j == 0)
	{
		std::cout << "No hand to show\n";
		return -1;
	}
	
	for (int i = 0; i < j; i++)
	{
		SetConsoleTextAttribute(hConsole,
			getColorText(players_[whoseTurn].handPos(i).getTileColors()[TOP]));
		std::cout << "  #  ";
		SetConsoleTextAttribute(hConsole, getColorText(-1));
	}
		std::cout << "\n";
		
	for (int i = 0; i < j; i++)
	{
		SetConsoleTextAttribute(hConsole,
			getColorText(players_[whoseTurn].handPos(i).getTileColors()[LEFT]));
		std::cout << " #";
		SetConsoleTextAttribute(hConsole, getColorText(-1));
		if (players_[whoseTurn].handPos(i).hasAnimalToken())
		{
			std::cout << "*";
		}
		else
		{
			std::cout << " ";
		}
		SetConsoleTextAttribute(hConsole,
			getColorText(players_[whoseTurn].handPos(i).getTileColors()[RIGHT]));
			std::cout << "# ";
			SetConsoleTextAttribute(hConsole, getColorText(-1));
	}
	std::cout << "\n";


	for (int i = 0; i < j; i++)
	{
		SetConsoleTextAttribute(hConsole,
			getColorText(players_[whoseTurn].handPos(i).getTileColors()[BOT]));
		std::cout << "  #  ";
		SetConsoleTextAttribute(hConsole, getColorText(-1));

	}

	std::cout << "\n";

	return 0;
}