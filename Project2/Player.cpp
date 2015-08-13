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
	playerName_ = NULL;
	numCoins_ = 0;
	colorCards_ = std::vector<int> (ORANGE + 1, 0);
	hand = std::vector<LakeTile>( 0,LakeTile());
	points_ = 0;
	orientation = 0;

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

LakeTile Player::handPos(int n)
{

	return hand[n];
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
		return 0;
	}
	


}
int Player::incCoins()
{
	numCoins_++;
	return 0;
}

int Player::decCoins()
{
	numCoins_--;
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