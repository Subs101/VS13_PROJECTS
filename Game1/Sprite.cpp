#include "Sprite.h"
#include "SDL.h"
#include "graphics.h"

struct Graphics;

Sprite::Sprite(Graphics& graphics,
	const std::string& file_path,
	units::Pixel source_x, units::Pixel source_y,
	units::Pixel width, units::Pixel height)
{
	const bool black_is_transparent = true;
	sprite_sheet_ = graphics.loadImage(file_path,black_is_transparent);
	source_rect_.x = source_x;
	source_rect_.y = source_y;
	source_rect_.w = width;
	source_rect_.h = height;
}


void Sprite::draw(Graphics& graphics, units::Game x, units::Game y)
{
	SDL_Rect dest_rect;
	dest_rect.x = units::gameToPixel(x);
	dest_rect.y = units::gameToPixel(y);

	graphics.blitSurface(sprite_sheet_, &source_rect_, &dest_rect);
	
}

