#ifndef _SPRITE_S
#define _SPRITE_S

#include <string>
#include <SDL.h>
#include "Units.h"


struct SDL_Rect;
struct SDL_Surface;
struct Graphics;
struct Sprite
{


Sprite(Graphics& graphics,
	const std::string& file_path,
	units::Pixel source_x, units::Pixel source_y,
	units::Pixel width, units::Pixel height);
	
	virtual void update(units::MS/*elapsed_time_ms*/) = 0;
	

void draw(Graphics& graphics, units::Game x, units::Game y);
protected:
	SDL_Rect source_rect_;

private:
	SDL_Surface* sprite_sheet_;
	

};


#endif