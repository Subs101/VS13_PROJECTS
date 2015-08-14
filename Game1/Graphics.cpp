#include "Graphics.h"
#include "SDL.h"
#include "game.h"
#include "Units.h"

namespace
{

	const int bitperpixel = 32;
}

struct SDL_Surface;

Graphics::Graphics()
{
	screen_ = SDL_SetVideoMode(units::tileToPixel(Game::screenWidth), 
					units::tileToPixel(Game::screenHeight), 
					bitperpixel,
					SDL_HWSURFACE );

}

Graphics::~Graphics()
{
	for (SpriteMap::iterator iter = sprite_sheets_.begin(); iter != sprite_sheets_.end(); ++iter)
	{
		SDL_FreeSurface(iter->second);
	}
	SDL_FreeSurface(screen_);
}

Graphics::SurfaceID Graphics::loadImage(const std::string& file_path,bool black_is_transparent)
{
	//havent loaded sprite sheet yet
	if (sprite_sheets_.count(file_path) == 0)
	{
		//load it in now
		sprite_sheets_[file_path] = SDL_LoadBMP(file_path.c_str());
		if (black_is_transparent)
		{
			SDL_SetColorKey(sprite_sheets_[file_path], SDL_SRCCOLORKEY, 0/*black*/);
		}
	}
	return sprite_sheets_[file_path];
}


void Graphics::blitSurface(
	SurfaceID source,
	SDL_Rect* source_rect,
	SDL_Rect* dest_rect)
{
	SDL_BlitSurface(source, source_rect, screen_, dest_rect);


}
void Graphics::flip()
{
	SDL_Flip(screen_);
}

void Graphics::clear() {
	SDL_FillRect(screen_,NULL,0);
}


void Graphics::setCamera(int x_, int y_)
{
	camera_.w = units::tileToPixel( Game::screenWidth);
	camera_.h = units::tileToPixel(Game::screenHeight);

	//Center the camera over the dot
	camera_.x = (x_ + 0.5*units::tileToPixel(1) ) - units::tileToPixel( Game::screenWidth)/2;
	camera_.y = (y_ + 0.5*units::tileToPixel(1) ) - units::tileToPixel(Game::screenHeight )/ 2;

	//Keep the camera_ in bounds.
	if (camera_.x < 0)
	{
		camera_.x = 0;
	}
	if (camera_.y < 0)
	{
		camera_.y = 0;
	}
	if (camera_.x > Game::LEVEL_WIDTH - camera_.w)
	{
		camera_.x = Game::LEVEL_WIDTH - camera_.w;
	}
	if (camera_.y > Game::LEVEL_HEIGHT - camera_.h)
	{
		camera_.y = Game::LEVEL_HEIGHT - camera_.h;
	}
}