#ifndef ENEMY_H_
#define ENEMY_H_
#include "Units.h"
#include <boost/shared_ptr.hpp>

struct Sprite;
struct Graphics;
struct Enemy
{
	Enemy(Graphics& graphics, units::Game x, units::Game y);

	void draw(Graphics& graphics) const;
	void update(units::MS elapsed_time_ms);

private:
	boost::shared_ptr<Sprite> sprite_;
	units::Game x_, y_;
	

	units::Velocity velocity_x_;

	units::Frame pauseFrames_ ;
	

	bool pause_;
	bool flag_;


};

#endif