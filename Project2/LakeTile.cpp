#include "LakeTile.h"
#include <vector>

namespace
{
	const int num_sides = 4;
}



LakeTile::LakeTile() 
{
	 
	 tileColors_ = std::vector<int> (num_sides, 0);
	 animalToken = false;

}



LakeTile::LakeTile(int colorTop, //paramaterized constructor for creating all unique tiles
	int colorRight,
	int colorBot,
	int colorLeft,
	bool token)
{
	tileColors_ = std::vector<int>(num_sides, 0);
	tileColors_[TOP] = colorTop;
	tileColors_[RIGHT] = colorRight;
	tileColors_[BOT] = colorBot;
	tileColors_[LEFT] = colorLeft;
	animalToken = token;

}

std::vector<int> LakeTile::getTileColors()
{
	return tileColors_;
}

void LakeTile::setTile(int colorTop,
	int colorRight,
	int colorBot,
	int colorLeft,
	bool token)
{
	tileColors_ = std::vector<int>(num_sides, 0);
	tileColors_[TOP] = colorTop;
	tileColors_[RIGHT] = colorRight;
	tileColors_[BOT] = colorBot;
	tileColors_[LEFT] = colorLeft;
	animalToken = token;
}

bool LakeTile::hasAnimalToken()
{
	if (animalToken)
	{
		return true;
	}
	else
	{
		return false;
	}
}

LakeTile LakeTile::operator=(LakeTile rhs)
{
	tileColors_ = rhs.tileColors_;
	
	animalToken = rhs.animalToken;

	return *this;
}

int LakeTile::rotateTileCW()
{
	int tempColor,tempColor2,tempColor3,tempColor4;
	tempColor = tileColors_[TOP];
	tempColor2 = tileColors_[RIGHT];
	tempColor3 = tileColors_[BOT];
	tempColor4 = tileColors_[LEFT];

	tileColors_[TOP] = tempColor4;
	tileColors_[RIGHT] = tempColor;
	tileColors_[BOT] = tempColor2;
	tileColors_[LEFT] = tempColor3;

	return 0;

}