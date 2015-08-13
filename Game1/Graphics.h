#ifndef _GRAPHICS_G
#define _GRAPHICS_G
#include <string>
#include "SDL.h"
#include <map>

struct SDL_Rect;
struct SDL_Surface;

struct Graphics
{
	typedef SDL_Surface* SurfaceID;
	Graphics();
	~Graphics();

	SurfaceID loadImage(const std::string& file_path, bool black_is_transparent = false);

	void blitSurface(
		SurfaceID soruce,
		SDL_Rect* source_rect,
		SDL_Rect* dest_rect);

	void flip();
	void clear();
	void setCamera(int x_, int y_);

	int getCameraX(){ return camera_.x; };
	int getCameraY(){ return camera_.y; };

private:
	typedef std::map<std::string, SDL_Surface*> SpriteMap;
	SpriteMap sprite_sheets_;
	SDL_Surface* screen_;
	SDL_Rect camera_;

};


#endif