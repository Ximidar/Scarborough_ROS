/*
 * motors.h
 *
 *  Created on: Mar 9, 2016
 *      Author: sdcr
 */

#ifndef MOTORS_SCARBOROUGH_H_
#define MOTORS_SCARBOROUGH_H_


 // functions for writing to the i2c bus
#include <iostream>
#include "scarborough/Motor_Speed.h"
#include "scarborough/Kill_Switch.h"
#include "../HandlerNames/HANDLER_NAMES.h"
#include "ros/ros.h"
#include <stdlib.h>
#include <algorithm>
#include <string>


using namespace std;

/*
 * This class is used to set the PID motor values from the arduino to the individual motors.
 * we will grab the motor values and set them to a class variable then push that class variable to the
 * individual motors over i2c all at once. This will constantly update the motor speeds.
 */
class Motors_Scarborough{

public:
	void init();
	void set_motor_speed();
	void get_motor_values(scarborough::Motor_Speed _input);
	bool check_kill_switch();
	int arraySize(double array[]);
	int i2cConvert(int address);
	void kill_motors();
	scarborough::Motor_Speed input;
	bool killer;

	

	int throttle;


private:
	//functions

	//variables if needed





};



#endif /* MOTORS_H_ */
