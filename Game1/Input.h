#ifndef INPUT_H_
#define INPUT_H_

#include <map>
#include <SDL.h>

struct Input {
	void beginNewFrame();
	void keyDownEvent(const SDL_Event& e);
	void keyUpEvent(const SDL_Event& e);

	bool wasKeyPressed(SDLKey key);
	bool wasKeyReleased(SDLKey key);
	bool isKeyHeld(SDLKey key);
private:
	std::map<SDLKey, bool> held_keys_;
	std::map<SDLKey, bool> pressed_keys_;
	std::map<SDLKey, bool> released_keys_;
};

#endif

