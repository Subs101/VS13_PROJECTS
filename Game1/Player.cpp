#include "Player.h"
#include "AnimatedSprite.h"
#include "game.h"
#include <cmath>
#include "Sprite.h"
#include "map.h"
#include "Rectangle.h"

//Collision Rect
 Rectangle CollisionX(8, 16, 20, 5);//megaman hitbox x dir
 Rectangle CollisionY(10, 7, 5, 25);//megaman hitbox y dir


 struct CollisionInfo
 {
	 bool collided;
	 units::Tile row, col;
 };

 CollisionInfo getWallCollisionInfo(const Map& map, const Rectangle& rectangle)
 {
	 CollisionInfo info = { false, 0, 0 };
	 std::vector<Map::CollisionTile> tiles(map.getCollidingTiles(rectangle));

	 for (size_t i = 0; i < tiles.size(); ++i)
	 {

		 if (tiles[i].tile_type == Map::WALL_TILE){
			 info = { true, tiles[i].row, tiles[i].col };


			 break;

		 }
	 }
	 return info;
 }
 

bool operator<(const Player::SpriteState& a, const Player::SpriteState& b)
{
	if (a.motion_type != b.motion_type)
	{
		//true is a = standing
		//false is a = walking
		return a.motion_type < b.motion_type;
	}
	if (a.horizontal_facing != b.horizontal_facing)
	{
		//true is  a= left
		//false is a = right
		return a.horizontal_facing < b.horizontal_facing;
	}
	// a = b
	return false;
}


Player::Player(Graphics& graphics, units::Game (x), units::Game( y)) : x_(x),
y_(y), velocity_x_(0.0f), acceleration_x_(0.0f), horizontal_facing_(RIGHT),
velocity_y_(0.0f), on_ground_(false), alive_(true)
{
	initSprites(graphics);
}


void Player::update(units::MS elapsed_time_ms,const Map& map){

	sprites_[getSpriteState()]->update(elapsed_time_ms);
	
	updateX(elapsed_time_ms,map);
	updateY(elapsed_time_ms, map);
	


}

void Player::updateX(units::MS elapsed_time_ms, const Map& map)
{
	//calc acceleration
	units::Acceleration acceleration_vec_x = 0.0f;
	if (acceleration_x_ < 0)
	{
		//moving left
		if (on_ground())
		{
			if (sprint_)
			{
				acceleration_vec_x = -sprintAcceleration;
			}
			else
			{
				acceleration_vec_x = -walkAcceleration;
			}

		}
		else
		{
			acceleration_vec_x = -airAcceleration;
		}


	}	  
	else if (acceleration_x_ > 0)
	{
		//moving right
		if (on_ground())
		{
			if (sprint_)
			{
				acceleration_vec_x = sprintAcceleration;
			}
			else
			{
				acceleration_vec_x = walkAcceleration;
			}

		}
		else
		{
			acceleration_vec_x = airAcceleration;
		}


	}

	//calc velocity
	velocity_x_ += acceleration_vec_x *elapsed_time_ms;

	if (acceleration_x_ < 0.0f){

		if (sprint_)
		{
			velocity_x_ = std::fmax(velocity_x_, -maxSprintSpeedx);
		}
		else
		{
			velocity_x_ = std::fmax(velocity_x_, -maxSpeedx);
		}
		
	}
	else if (acceleration_x_ > 0.0f)
	{
			if (sprint_)
		{
			velocity_x_ = std::fmin(velocity_x_, maxSprintSpeedx);
		}
		else
		{
			velocity_x_ = std::fmin(velocity_x_, maxSpeedx);
		}
	}
	else if (on_ground()){
		velocity_x_ = velocity_x_ > 0.0f ?
			std::fmax(0.0f, velocity_x_*(1 - frictionFactor) ):
			std::fmin(0.0f, velocity_x_* (1 - frictionFactor));
		

	}


	
	const units::Game delta = round(velocity_x_*elapsed_time_ms);
	

	if (delta >= 0.0f)
	{

		
		CollisionInfo info = getWallCollisionInfo(map, rightCollision(delta));

		if (info.collided)
		{
			
			x_ = units::tileToGame(info.col) - CollisionX.right();
			velocity_x_ = 0.0f;
		}
		else
		{
			x_ += delta;
		}
		//check coll in other ditection
		info = getWallCollisionInfo(map, leftCollision(0));
		if (info.collided)
		{
			x_ = units::tileToGame(info.col) + CollisionX.right();
		}
		

	}
	else{
		CollisionInfo info = getWallCollisionInfo(map, leftCollision(delta));

		if (info.collided){
			x_ = units::tileToGame(info.col) + CollisionX.right();
			velocity_x_ = 0.0f;
		}
		else{
			x_ += delta;
		}

		
		//check coll in other ditection
		
		info = getWallCollisionInfo(map, rightCollision(0));
		if (info.collided)
		{
			x_ = units::tileToPixel(info.col) - CollisionX.right();
		}
		

	}

}


void Player::updateY(units::MS elapsed_time_ms, const Map& map)
{


	const  units::Acceleration activeGravity = jump_active_  && velocity_y_ < 0.0f ? jumpGravity : gravity;

	
	//Update velocity
	velocity_y_ = std::fmin(velocity_y_ + activeGravity * elapsed_time_ms, maxSpeedy);



	//calculate delta hitbox
	const units::Game delta = round(velocity_y_*elapsed_time_ms);
	

	if (delta >= 0.0f){

		//check collision in dir of delta
		CollisionInfo info = getWallCollisionInfo(map, bottomCollision(delta));

		//react to collision


		if (info.collided)
		{
			y_ = units::tileToGame(info.row)  - CollisionY.bottom();
			velocity_y_ = 0.0f;
			on_ground_ = true;
		}
		else{
			y_ += delta;
			on_ground_ = false;
		}


		//check collision in other dir
		info = getWallCollisionInfo(map, topCollision(0));
		if (info.collided)
		{
			y_ = units::tileToGame(info.row) + CollisionY.height();
		}
	}
	
	else//jumping delta < 0
	{
		CollisionInfo info = getWallCollisionInfo(map, topCollision(delta));

		if (info.collided)
		{
			y_ = units::tileToGame(info.row) + CollisionY.height();
			velocity_y_ = 0.0f;
		}
		else
		{
			y_ += delta;
			on_ground_ = false;
		}

		//check in other dir
		info = getWallCollisionInfo(map, bottomCollision(0));
		if (info.collided)
		{
			y_ = units::tileToGame(info.row)  - CollisionY.bottom();
			on_ground_ = true;
		}

	}
	

	}






void Player::draw(Graphics& graphics)
{
	graphics.setCamera(x_, y_);//cam
	sprites_[getSpriteState()]->draw(graphics, x_ - graphics.getCameraX(), y_ - graphics.getCameraY());
}

void Player::startMovingLeft(){
	acceleration_x_ = -1;
	horizontal_facing_ = LEFT;
}
void Player::startMovingRight(){
	acceleration_x_ = 1;
	horizontal_facing_ = RIGHT;
}
void Player::stopMoving(){
	acceleration_x_ = 0;
}



void Player::startJump()
{
	jump_active_ = true;

	if (on_ground()){	
		velocity_y_ = - jumpSpeed;
	}

}

void Player::stopJump()
{
	jump_active_ = false;
	
}

void Player::die()
{
	alive_ = false;
}
void Player::revive()
{
	alive_ = true;
}


void Player::setSprint(bool sprint)
{
	sprint_ = sprint;
}

void Player::initSprites(Graphics& graphics)
{
	sprites_[SpriteState(WALKING, RIGHT)] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, 
		"megaman_walk.bmp", 0, 0,
		units::tileToPixel(1), 
		units::tileToPixel(1), 
		24, 11));

	sprites_[SpriteState(STANDING, RIGHT)] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics,
		"megaman_walk.bmp", 0, units::tileToPixel(1)*2,
		units::tileToPixel(1),
		units::tileToPixel(1),
		1,3));

	sprites_[SpriteState(WALKING, LEFT)] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics,
		"megaman_walk.bmp", 0, units::tileToPixel(1),
		units::tileToPixel(1),
		units::tileToPixel(1),
		24, 11));

	sprites_[SpriteState(STANDING, LEFT)] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics,
		"megaman_walk.bmp", 0, units::tileToPixel(1)*3,
		units::tileToPixel(1),
		units::tileToPixel(1),
		1, 3));

	sprites_[SpriteState(JUMPING, LEFT)] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics,
		"megaman_walk.bmp", 3*units::tileToPixel(1), 3*units::tileToPixel(1),
		units::tileToPixel(1),
		units::tileToPixel(1), 
		3, 3));

	sprites_[SpriteState(JUMPING, RIGHT)] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics,
		"megaman_walk.bmp", 3*units::tileToPixel(1), 2*units::tileToPixel(1),
		units::tileToPixel(1),
		units::tileToPixel(1), 
		3, 3));

	
	sprites_[SpriteState(FALLING, RIGHT)] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics,
		"megaman_walk.bmp", 6*units::tileToPixel(1), 2*units::tileToPixel(1),
		units::tileToPixel(1),
		units::tileToPixel(1),
		3, 3));

	sprites_[SpriteState(FALLING, LEFT)] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics,
		"megaman_walk.bmp", 6 * units::tileToPixel(1), 3 * units::tileToPixel(1),
		units::tileToPixel(1),
		units::tileToPixel(1), 
		3, 3));


	sprites_[SpriteState(DEAD, RIGHT)] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics,
		"megaman_walk.bmp", 0, 4 * units::tileToPixel(1),
		units::tileToPixel(1),
		units::tileToPixel(1),
		5, 9));

	sprites_[SpriteState(DEAD, LEFT)] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics,
		"megaman_walk.bmp", 0, 5 * units::tileToPixel(1),
		units::tileToPixel(1),
		units::tileToPixel(1), 
		5, 9));



}
Player::SpriteState Player::getSpriteState()
{
	MotionType motion;
	if (on_ground())
	{
		motion = acceleration_x_ == 0 ? STANDING : WALKING;
	}
	else
	{
		//in air
		if (velocity_y_ < 0)
		{
			motion = JUMPING;
		}
		else
		{
			motion = FALLING;
		}
	}

	if (!alive_)
	{
		motion = DEAD;
	}

	
		
	return SpriteState(motion,
		horizontal_facing_);

}



Rectangle Player::leftCollision(units::Game delta) const
{
	assert(delta <= 0);
	return Rectangle(
		x_ + CollisionX.left() + delta,
		y_ + CollisionX.top() ,
		CollisionX.width() / 2 - delta,
		CollisionX.height()
		);


}
Rectangle Player::rightCollision(units::Game delta) const
{
	assert(delta >= 0);
	return Rectangle
	{
		//change?
		x_ + (CollisionX.left() + CollisionX.right() )/2,
		y_ + CollisionX.top(),
		CollisionX.width()/2  + delta,
		CollisionX.height()
	};
}

Rectangle Player::topCollision(units::Game delta) const
{
	assert(delta <= 0);
	return Rectangle
	{
		x_ + CollisionY.left(),
		y_ + CollisionY.top()+ delta,
		CollisionY.width(),
		CollisionY.height() / 2 - delta
	};
}
Rectangle Player::bottomCollision(units::Game delta) const
{
	assert(delta >= 0);
	return Rectangle
	{
		x_ + CollisionY.left(),
		y_ + CollisionY.top() + CollisionY.height()/2,
		CollisionY.width(),
		CollisionY.height() / 2 + delta
	};
}



