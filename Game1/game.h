#ifndef _GAME_H
#define _GAME_H
#include <boost/scoped_ptr.hpp>
#include "Units.h"

struct Sprite;
struct Graphics;
struct Player;
struct Map;
struct Input;
struct Enemy;

struct Game
{
	Game();
	~Game();

	//static
	//static int tileSize;
	static units::Tile screenWidth;
	static units::Tile screenHeight;
	

	static int LEVEL_HEIGHT;
	static int LEVEL_WIDTH;

private:


	void eventLoop();
	void handleInput(Input input);
	void update(units::MS elapsed_time_ms);
	void draw(Graphics& graphics);


	bool running_;

	boost::scoped_ptr<Player> player_;
	boost::scoped_ptr<Enemy> enemy_;
	boost::scoped_ptr<Map> map_;
};



#endif //GAME_H_