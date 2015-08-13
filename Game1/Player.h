#ifndef PLAYER_H_
#define PLAYER_H_
#include "Sprite.h"
#include <boost/shared_ptr.hpp>
#include <map>
#include "map.h"
#include "Rectangle.h"
#include "game.h"
#include "Units.h"

struct Sprite;
struct Graphics;
struct Map;

namespace
{

	const float frictionFactor = 0.3f; 

	const units::Acceleration sprintAcceleration = (0.004); 
	const units::Acceleration walkAcceleration = (0.002f); 
	const units::Acceleration airAcceleration = (0.0005f); 
	const units::Acceleration gravity = (0.002f); 
	const units::Acceleration jumpGravity = (0.0005125f); 

	const units::Velocity maxSpeedx = ( 0.125f); 
	const units::Velocity maxSprintSpeedx = (0.1875f);
	const units::Velocity maxSpeedy = (0.325f);
	const units::Velocity jumpSpeed = (0.25f);
	

}

struct Player
{
	Player(Graphics& graphics, units::Game x, units::Game y);

	void update(units::MS elapsed_time_ms,const Map& map);
	void updateX(units::MS elapsed_time_ms, const Map& map);
	void updateY(units::MS elapsed_time_ms, const Map& map);

	void draw(Graphics& graphics);

	void startMovingLeft();
	void startMovingRight();
	void stopMoving();
	void setSprint(bool sprint);

	void startJump();
	void stopJump();

	void die();
	void revive();

	
	

private:

	
	

	enum MotionType{
		STANDING,
		WALKING,
		JUMPING,
		FALLING,
		DEAD,
	};

	enum HorizontalFacing{
		LEFT,
		RIGHT
	};

	struct SpriteState {
		SpriteState(MotionType motion_type = STANDING,
		HorizontalFacing horizontal_facing = LEFT) :
		motion_type(motion_type),
		horizontal_facing(horizontal_facing){}

		MotionType motion_type;
		HorizontalFacing horizontal_facing;
	};




	//operator to reveal which way player sprite should be facing
	friend bool operator<(const SpriteState& a, const SpriteState& b);


	void initSprites(Graphics& graphics);

	//collision rectangles
	Rectangle leftCollision(units::Game delta) const;
	Rectangle rightCollision(units::Game delta) const;

	Rectangle topCollision(units::Game delta) const;
	Rectangle bottomCollision(units::Game delta) const;

	//player sprite map
	std::map<SpriteState, boost::shared_ptr<Sprite> > sprites_;
	SpriteState getSpriteState();


	//player x-direction kinematics
	units::Game x_;
	int acceleration_x_;
	HorizontalFacing horizontal_facing_;
	float velocity_x_;
	bool sprint_ = false;

	//player y-dir kinematics
	units::Game y_;
	units::Velocity velocity_y_;
	bool on_ground()const{ return on_ground_; }
	bool on_ground_;
	bool jump_active_ = false;

	


	//dead?
	bool alive_;

	

};
#endif