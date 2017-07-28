#ifndef DEAD_MOTORS_H
#define DEAD_MOTORS_H
#include "scarborough/Motor_Speed.h"
#include "scarborough/Desired_Directions.h"
#include "scarborough/YPR.h"
#include "scarborough/Depth.h"
#include <iostream>

using namespace std;

class Dead_Motors
{
public:
	Dead_Motors();
	~Dead_Motors();

	int adjust_motor(bool dive, int motor, int adjustment_amount, double max_offset, double orientation, double desired_orientation);
	int clamp(int value);
	int clamp_dive(int value);
	void dive(scarborough::Depth cur_depth, scarborough::YPR cur_orientation, scarborough::Desired_Directions des_orientation);
	void keep_heading(scarborough::Depth cur_depth, scarborough::YPR cur_orientation, scarborough::Desired_Directions des_orientation);

	scarborough::Motor_Speed motor_output;


	
};

#endif