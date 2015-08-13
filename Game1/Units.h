#ifndef UNITS_H_
#define UNITS_H_

#include <math.h>

namespace units
{
	typedef float Game; // float for extra precision. Intrinsic units of position
	typedef int Pixel; // integer for discrete units
	typedef unsigned int Tile;
	typedef unsigned int Frame;

	typedef int MS; //discrete milisec unisnged int matches SDL.
	typedef unsigned int FPS; //Frames per sec (Hz)

	typedef float Velocity; // Game / MS
	typedef float Acceleration; // Game / MS / MS

	namespace{

		const Game tileSize = 32.0f;
	}

	
	inline Pixel gameToPixel(Game game)
	{
		return Pixel(round(game * 32 / 32));
	}
	
	inline Tile gameToTile(Game game)
	{
		return Tile(game / tileSize);
	}

	inline Game tileToGame(Tile tile)
	{
		return tile * tileSize;
	}
	
	inline Pixel tileToPixel(Tile tile)
	{
		return gameToPixel(tileToGame(tile));
	}

}

#endif