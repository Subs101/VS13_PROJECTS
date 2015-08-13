#ifndef LAKETILES_H_
#define LAKETILES_H_
#include <vector>
#include <iostream>

enum Cards
{
	BLACK,
	RED,
	BLUE,
	WHITE,
	PINK,
	GREEN,
	ORANGE,

};

enum Sides
{
	TOP,
	RIGHT,
	BOT,
	LEFT,
};


struct LakeTile
{

	LakeTile();//def constructor for gameboard

	LakeTile(int colorTop, //paramaterized constructor for creating all unique tiles
			int colorRight,
			int colorBot, 
			int colorLeft,
			bool animalToken);

	std::vector<int> getTileColors();
	bool hasAnimalToken();
	int rotateTileCW();

	LakeTile operator=(LakeTile rhs);

	void setTile(int colorTop,
		int colorRight,
		int colorBot,
		int colorLeft,
		bool token);


private:

	bool animalToken;
	std::vector<int> tileColors_;
};



#endif