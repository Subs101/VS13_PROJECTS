#ifndef MAP_H_
#define MAP_H_
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
#include "Units.h"
#include "Backdrop.h"

struct Sprite;
struct Graphics;
struct Rectangle;

struct Map
{

	enum TileType
	{
		AIR_TILE,
		WALL_TILE,
	};

	struct CollisionTile
	{
		CollisionTile(int row, int col, TileType tile_type) :
		row(row), col(col), tile_type(tile_type){}


		TileType tile_type;
		int row, col;


	};



	static Map* createTestMap(Graphics& graphics);

	std::vector<CollisionTile> getCollidingTiles(const Rectangle& rectangle) const;

	void update(units::MS elapsed_time_ms);
	void draw(Graphics& grpahics) const;
	void drawBackdrop(Graphics& graphics) const;

private:

	struct Tile
	{
		Tile(TileType tile_type = AIR_TILE,
		boost::shared_ptr<Sprite> sprite = boost::shared_ptr<Sprite>()) :
		tile_type(tile_type), sprite(sprite){}
		
		TileType tile_type;
		boost::shared_ptr<Sprite> sprite;
	};
	std::vector<std::vector<boost::shared_ptr<Sprite> > > background_tiles_;
	boost::scoped_ptr<Backdrop> backdrop_;
	std::vector < std::vector<Tile> > tiles_;
};
#endif