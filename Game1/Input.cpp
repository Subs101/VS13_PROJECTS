#include "Input.h"

void Input::beginNewFrame()
{
	pressed_keys_.clear();
	released_keys_.clear();
}

void Input::keyDownEvent(const SDL_Event& e)
{
	pressed_keys_[e.key.keysym.sym] = true;
	held_keys_[e.key.keysym.sym] = true;
	
}

void Input::keyUpEvent(const SDL_Event& e)
{
	
	released_keys_[e.key.keysym.sym] = true;
	held_keys_[e.key.keysym.sym] = false;
}

bool Input::wasKeyPressed(SDLKey key)
{
	return pressed_keys_[key];
}

bool Input::wasKeyReleased(SDLKey key)
{
	return released_keys_[key];
}

bool Input::isKeyHeld(SDLKey key)
{
	return held_keys_[key];
}