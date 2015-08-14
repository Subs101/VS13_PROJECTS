#include "Backdrop.h"
#include "SDL.h"
#include "game.h"
#include "Units.h"



namespace{
	const units::Tile backgroundSizeX = 20;
	const units::Tile backgroundSizeY = 15;
}

FixedBackdrop::FixedBackdrop(const std::string& path, Graphics& graphics)
{
	surface_id_ = graphics.loadImage(path);

}

void FixedBackdrop::draw(Graphics& graphics) const 
{
	

	for (units::Tile x = 0; x < Game::screenWidth; x += backgroundSizeX)
	{
		for (units::Tile y = 0; y < Game::screenHeight; y += backgroundSizeY)
		{
			SDL_Rect dest_rect;
			dest_rect.x = units::tileToPixel(x);
			dest_rect.y = units::tileToPixel(y);
			graphics.blitSurface(surface_id_, NULL, &dest_rect);
		}
	}

}