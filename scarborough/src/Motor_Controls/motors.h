/*
 * motors.h
 *
 *  Created on: Mar 9, 2016
 *      Author: sdcr
 */

#ifndef MOTORS_H_
#define MOTORS_H_

#include <array>
#include "I2Cdev.h" // functions for writing to the i2c bus
#include <iostream>
#include "scarborough/Motor_Speed.h"

/*
 * This class is used to set the PID motor values from the arduino to the individual motors.
 * we will grab the motor values and set them to a class variable then push that class variable to the
 * individual motors over i2c all at once. This will constantly update the motor speeds.
 */
class motors{

public:
	void init();
	void set_motor_speed();
	void get_motor_values(double motor_raw[6]);

private:
	//variables if needed
	int motor_val[6];



};



#endif /* MOTORS_H_ */
