#include "game.h"
#include "SDL.h"
#include "Graphics.h"
#include "Player.h"
#include "Input.h"
#include "map.h"
#include "enemy.h"
namespace
{
	const units::FPS fps = 60;
}

//Screen atributes
units::Tile Game::screenWidth = 20;
units::Tile Game::screenHeight = 15;
//int Game::tileSize = 32;


//The dimensions of the level
int Game::LEVEL_WIDTH = 1280;
int Game::LEVEL_HEIGHT = 960;





Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	eventLoop();
}

Game::~Game()
{
	SDL_Quit();
}

void Game::eventLoop()
{
	Graphics graphics;
	Input input;
	SDL_Event e;
	

	player_.reset(new Player(graphics, units::tileToGame(screenWidth/2),units::tileToGame(screenHeight/2)));
	map_.reset(Map::createTestMap(graphics));

	enemy_.reset(new Enemy(graphics, units::tileToGame(7), units::tileToGame(8)+20));

	running_ = true;

	units::MS last_update_time = SDL_GetTicks();
	const units::MS start_time_ms = SDL_GetTicks();
	while (running_)
	{
		input.beginNewFrame();
		
		/*time to execute inputs +  update and draw  = elapsed_time*/
		
		while (SDL_PollEvent(&e))
		{
			
			switch (e.type)
			{
			case SDL_KEYDOWN:

				input.keyDownEvent(e);
				break;

			case SDL_KEYUP:

				input.keyUpEvent(e);
				break;

			default:break;

			}
		}

		handleInput(input);

		const units::MS current_time_ms = SDL_GetTicks();


		draw(graphics);
		update(current_time_ms-last_update_time);
		


		last_update_time = current_time_ms;

		


		/* ---- elapsed time block ----*/
		const units::MS elapsed_time_ms = SDL_GetTicks() - start_time_ms;
		const units::MS ms_per_frame = 1000 / fps;

		//Cap the frame rate
		if (elapsed_time_ms < ms_per_frame)
		{
			SDL_Delay(ms_per_frame - elapsed_time_ms);
		}
		else
		{
			SDL_Delay(ms_per_frame);
		}
		
		
		

	}

}

void Game::update(units::MS elapsed_time_ms)
{
	enemy_->update(elapsed_time_ms);
	player_->update(elapsed_time_ms,*map_);
	
	map_->update(elapsed_time_ms);
}
void Game::draw(Graphics& graphics)
{
	graphics.clear();
	map_->drawBackdrop(graphics);
	enemy_->draw(graphics);
	player_->draw(graphics);
	map_->draw(graphics);
	graphics.flip();
}


void Game::handleInput(Input input)
{
	if (input.wasKeyPressed(SDLK_ESCAPE))
	{
		running_ = false;
	}

	//Horizontal movement
	if (input.isKeyHeld(SDLK_a) && input.isKeyHeld(SDLK_d))
	{
		player_->stopMoving();
	}

	else if (input.isKeyHeld(SDLK_a))
	{
		if (input.isKeyHeld(SDLK_LSHIFT))
		{
			player_->setSprint(true);
		}
		else
		{
			player_->setSprint(false);
		}

		player_->startMovingLeft();
	}
	else if (input.isKeyHeld(SDLK_d))
	{

		if (input.isKeyHeld(SDLK_LSHIFT))
		{
			player_->setSprint(true);
		}
		else
		{
			player_->setSprint(false);
		}

		player_->startMovingRight();

	}
	else
	{
		player_->stopMoving();
	}



	if (input.wasKeyPressed(SDLK_w))
	{
		player_->startJump();
	}
	if (input.wasKeyReleased(SDLK_w))
	{
		player_->stopJump();
	}

	if (input.wasKeyPressed(SDLK_z))
	{
		player_->die();
	}
	if (input.wasKeyPressed(SDLK_x))
	{
		player_->revive();
	}

}

