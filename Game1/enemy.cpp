#include "enemy.h"
#include "AnimatedSprite.h"
#include "Units.h"
#include "Graphics.h"
#include "game.h"

namespace
{
	const units::Frame numFrames = 9;
	const units::FPS fps_animation = 10;

	
	const units::Game xi_ = 228;//units::tileToGame(7);
	//const units::Game yi_ = //units::tileToGame(10);
}


Enemy::Enemy(Graphics& graphics,units::Game x, units::Game y) : x_(x), y_(y),
pauseFrames_(0), velocity_x_(0), pause_(false), flag_(false)
{


	sprite_ = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics,
		"enemy.bmp",
		0, 0,60,78,
		fps_animation, numFrames));

}

void Enemy::draw(Graphics& graphics) const
{

	sprite_->draw(graphics, x_ - graphics.getCameraX(), y_ - graphics.getCameraY());

}
void Enemy::update(units::MS elapsed_time_ms)
{
	


	//move right 3 tiles
	if ( (!pause_ ) && !flag_)
	{
		velocity_x_ = 0.1;
		x_ += elapsed_time_ms * velocity_x_;
		units::Game deltax = abs(x_ - xi_);

		if (deltax > units::tileToGame(3))
		{
			pause_ = true;
			velocity_x_ = 0;
		}

	}
	else if (pause_)
	{
		//pause for 1 sec
		pauseFrames_++;

		units::MS time = (pauseFrames_ / 60)*1000;
		
		if (time >= 3000)
		{
			pauseFrames_ = 0;
			pause_ = false;

			if (flag_ == true)
			{
				flag_ = false;
			}
			else
			{
				flag_ = true;
			}
			
		}


	}
	else
	{
		//move left 3 tiles
		velocity_x_ = -0.1;
		x_ += elapsed_time_ms * velocity_x_;
		units::Game deltax = abs(x_ - xi_);

		if (deltax > units::tileToGame(3))
		{
			pause_ = true;
			velocity_x_ = 0;
		}

	}


	sprite_->update(elapsed_time_ms);
}