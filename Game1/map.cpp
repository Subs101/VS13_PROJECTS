#include "map.h"
#include "Sprite.h"
#include "Graphics.h"
#include "game.h"
#include "AnimatedSprite.h"
#include "Rectangle.h"
#include "Backdrop.h"

using boost::shared_ptr;
using std::vector;
void Map::update(units::MS elapsed_time_ms)
{
	for (size_t row = 0; row < tiles_.size(); ++row)
	{
		for (size_t col = 0; col < tiles_[row].size(); ++col)
		{
			if (tiles_[row][col].sprite)
			{
				tiles_[row][col].sprite->update(elapsed_time_ms);
			}
		}
	}
}

vector<Map::CollisionTile> Map::getCollidingTiles(const Rectangle& rectangle) const
{
	const units::Tile first_row = units::gameToTile(rectangle.top());
	const units::Tile last_row = units::gameToTile( rectangle.bottom());
	const units::Tile first_col = units::gameToTile(rectangle.left());
	const units::Tile last_col = units::gameToTile(rectangle.right());

	const units::Tile rows = units::gameToTile(Game::LEVEL_HEIGHT);
	const units::Tile cols = units::gameToTile(Game::LEVEL_WIDTH);

	vector<CollisionTile> collision_tiles;
	
	if (last_row >= rows ||
		last_col >= cols ||
		first_col >= cols|| 
		first_row >= rows ||
		last_row < 0  ||
		first_row < 0 ||
		first_col < 0 ||
		last_col < 0)
	{
		return collision_tiles;
	}

	for (units::Tile row = first_row; row <= last_row; ++row){
		for (units::Tile col = first_col; col <= last_col; ++col){
			
			collision_tiles.push_back(CollisionTile(row, col, tiles_[row][col].tile_type));
		}
	}

	return collision_tiles;
}

Map* Map::createTestMap(Graphics& graphics)
{
	Map* map = new Map();

	map->backdrop_.reset(new FixedBackdrop("bd1.bmp", graphics));

	const units::Tile num_rows = units::gameToTile( Game::LEVEL_HEIGHT);
	const units::Tile num_cols = units::gameToTile(Game::LEVEL_WIDTH);


	//ensure tiles and bg tiles ais numrows x num cols in size
	map->tiles_ = vector<vector<Tile> >(
		num_rows, vector<Tile>(num_cols, Tile()));

	map->background_tiles_ = vector<vector<shared_ptr<Sprite> > >(
		num_rows, vector<shared_ptr<Sprite> >(
		num_cols, shared_ptr<Sprite>()));

	shared_ptr<Sprite> sprite(new AnimatedSprite(graphics, "PrtCave.bmp",
		units::tileToPixel(1), 0, units::tileToPixel(1), units::tileToPixel(1), 1, 1));

	shared_ptr<Sprite> doorTop(new AnimatedSprite(graphics, "bg.bmp", 0, 0, 
		units::tileToPixel(1), units::tileToPixel(1),
		1,1));

	shared_ptr<Sprite> doorBot(new AnimatedSprite(graphics, "bg.bmp", 0, 
		units::tileToPixel(1), units::tileToPixel(1),
		units::tileToPixel(1), 
		1, 1));

	Tile tile(WALL_TILE, sprite);

	for (int row = 14; row < 15; row++)
	{
		for (int col = 10; col < num_cols; ++col)
		{
			
			map->tiles_[row][col].sprite = tile.sprite;
			map->tiles_[row][col].tile_type = tile.tile_type;

		}

	}


	for (int row = 22; row < 23; row++)
	{
		for (int col = 0; col < num_cols; ++col)
		{

			map->tiles_[row][col].sprite = tile.sprite;
			map->tiles_[row][col].tile_type = tile.tile_type;

		}

	}

	map->tiles_[12][8].sprite = tile.sprite;
	map->tiles_[12][8].tile_type = tile.tile_type;

	for (int row = 11; row < 12; row++)
	{
		for (int col = 0; col < 7; ++col)
		{
			
				map->tiles_[row][col].sprite = tile.sprite;
				map->tiles_[row][col].tile_type = tile.tile_type;

			
		}

	}

	for (int row = 16; row < 17; row++)
	{
		for (int col = 9; col < 19; ++col)
		{

			map->tiles_[row][col].sprite = tile.sprite;
			map->tiles_[row][col].tile_type = tile.tile_type;


		}

	}



	for (int row = 8; row >= 0; row--)
	{
		for (int col = 15; col < num_cols; ++col)
		{
			if ((row == 5 || row == 6) && col == 15)
			{
	

			}
			else
			{
				map->tiles_[row][col].sprite = tile.sprite;
				map->tiles_[row][col].tile_type = tile.tile_type;
			}

		
		}

	}

	map->tiles_[6][12].sprite = tile.sprite;
	map->tiles_[6][12].tile_type = tile.tile_type;
		


	map->tiles_[7][6].sprite = tile.sprite;
	map->tiles_[7][6].tile_type = tile.tile_type;

	map->tiles_[10][3].sprite = tile.sprite;
	map->tiles_[10][3].tile_type = tile.tile_type;

	map->tiles_[9][3].sprite = tile.sprite;
	map->tiles_[9][3].tile_type = tile.tile_type;

	map->tiles_[6][7].sprite = tile.sprite;
	map->tiles_[6][7].tile_type = tile.tile_type;

	map->tiles_[8][3].sprite = tile.sprite;
	map->tiles_[8][3].tile_type = tile.tile_type;

	map->tiles_[10][6].sprite = tile.sprite;
	map->tiles_[10][6].tile_type = tile.tile_type;

	map->tiles_[9][3].sprite = tile.sprite;
	map->tiles_[9][3].tile_type = tile.tile_type;

	map->tiles_[10][3].sprite = tile.sprite;
	map->tiles_[10][3].tile_type = tile.tile_type;

	map->tiles_[10][4].sprite = tile.sprite;
	map->tiles_[10][4].tile_type = tile.tile_type;

	map->tiles_[7][7].sprite = tile.sprite;
	map->tiles_[7][7].tile_type = tile.tile_type;

	map->tiles_[10][6].sprite = tile.sprite;
	map->tiles_[10][6].tile_type = tile.tile_type;


	map->background_tiles_[9][15] = doorTop;
	map->background_tiles_[10][15] = doorBot;

	return map;
}

void Map::draw(Graphics& graphics) const
{

	for (size_t row = 0; row < tiles_.size(); ++row)
	{
		for (size_t col = 0; col < tiles_[row].size(); ++col)
		{
			if (tiles_[row][col].sprite)
			{
				tiles_[row][col].sprite->draw(graphics,units::tileToPixel(col)- graphics.getCameraX(),units::tileToPixel(row) - graphics.getCameraY());
			}
		}
	}
}

void Map::drawBackdrop(Graphics& graphics) const
{
	backdrop_->draw(graphics);


	for (size_t row = 0; row < tiles_.size(); ++row)
	{
		for (size_t col = 0; col < tiles_[row].size(); ++col)
		{
			if (background_tiles_[row][col])
			{
				background_tiles_[row][col]->draw(graphics, units::tileToPixel(col) - graphics.getCameraX(), units::tileToPixel(row) - graphics.getCameraY());
			}
		}
	}

}