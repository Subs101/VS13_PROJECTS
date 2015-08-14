#include "LakeTile.h"
#include "Game.h"
#include <vector>
#include "Player.h"

namespace
{
	const int MAX_HAND = 3;
}

Player::Player()
{
	playerName_;
	numCoins_ = 0;
	colorCards_ = std::vector<int> (ORANGE + 1, 0);
	hand = std::vector<LakeTile>( 0,LakeTile());
	points_ = 0;
	orientation = 0;
	AI_flag = false;

}

int Player::setFacing(int side)
{
	orientation = side;
	return 0;
}

int Player::drawTile(std::vector<LakeTile>& lakeTiles_)
{

	if (hand.size() < MAX_HAND   
		&& lakeTiles_.size() > 0)
	{
		hand.push_back(lakeTiles_.back());
		lakeTiles_.pop_back();
		return 0;
	}
	return -1;

}

int Player::handSize()
{
	return hand.size();
}
int Player::popHand()
{
	if (hand.size() > 0)
	{
		hand.pop_back();
		return 0;
	}
	return - 1;

}

LakeTile Player::topHand()
{
	if (hand.size() > 0)
	{
		return hand.back();
	}

}

LakeTile Player::handTile(int handPos)
{

	return hand[handPos];
}

int Player::drawColorCard(int color,std::vector<int>& deck)
{

	if (deck[color] > 0)
	{
		colorCards_[color]++;
		deck[color]--;
		return 0;
	}
	else
	{
		std::cout << "No more of " << color << " card\n";
		return -1;
	}
	


}
int Player::incCoins()
{
	numCoins_++;
	return 0;
}

int Player::decCoins()
{
	numCoins_ = numCoins_ - 2;
	return 0;
}

std::vector<int> Player::getColorHand()
{
	return colorCards_;
}
int Player::getCoins()
{
	return numCoins_;
}

int Player::facing()
{
	return orientation;
}

int Player::incPoints(int n)
{
	points_ += n;
	return 0;
}

int Player::decColorHand(int color)
{
	colorCards_[color]--;
	return 0;
}
int Player::getPoints()
{
	return points_;
}

int Player::rotateTile(int handPos, int iterations)
{
	for (int i = 0; i < iterations; i++)
	{
		hand[handPos].rotateTileCW();
	}
	return 0;
}


int Player::removeTile(int handPos)
{

	LakeTile temp1,temp2;

	switch (handSize())
	{
	case 1:
		if (handPos == 0)
		{
			popHand();
			return 0;
		}
		else
		{
			return -1;
		}

		break;
	case 2: 
		if (handPos == 0)
		{
			temp1 = hand[1];
			popHand();//remove tile 1
			popHand();//remove tile 0
			hand.push_back(temp1);//restore tile 1
		}
		else if (handPos == 1)
		{
			popHand();//remove tile 1
		}
		else
		{
			return -1;
		}
		break;

	case 3:
		if (handPos == 0)
		{
			temp1 = hand[2];
			temp2 = hand[1];
			popHand();//remove tile 2
			popHand();//remove tile 1
			popHand();//remove tile 0

			hand.push_back(temp2);//restore tile 1
			hand.push_back(temp1);//restore tile 1
		}
		else if (handPos == 1)
		{
			temp1 = hand[2];

			popHand();//remove tile 2
			popHand();//remove tile 1

			hand.push_back(temp1);//restore tile 2
		}
		else if (handPos == 2)
		{
			popHand();
		}
		else
		{
			return -1;
		}
		
		break;
	default: break;
	}

}
int Player::takeTurn(Game& game)
{
	if (!AI_flag)
	{
		while (game.actionMenu()>0);
		game.endTurn();
		return 0;
	}
	else
	{
		/*PLAYER AI*/
		//if 2 coins make exchange to yield buy
		//if buy criteria met do that..
		//placetile with most synergies
		game.endTurn();
		return 0;
	}
	
}

int Player::setName(std::string name)
{
	playerName_ = name;
	return 0;
}

std::string Player::getName()
{
	return playerName_;

}

int Player::setAI(bool flag)
{
	AI_flag = flag;
	return 0;
}
bool Player::getAI()
{
	return AI_flag;
}