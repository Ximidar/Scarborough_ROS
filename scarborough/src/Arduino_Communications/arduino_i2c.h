/*
 * arduino_i2c.h
 *
 *  Created on: Feb 1, 2016
 *      Author: sdcr
 */

#ifndef ARDUINO_I2C_H_
#define ARDUINO_I2C_H_

//definitions for I2Cdev
#define ARDUINO_DEV_ADDR 0x60
#define ARDUINO_REG_ADDR 0
#define ARDUINO_LENGTH 4

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "I2Cdev.h"
#include "scarborough/YPR.h"

using namespace std;

class ArdI2C{
public:
	ArdI2C();
	void get_accel_info(); // This will query the correct ROS stream to get the IMU data
	void ardWrite(); //write the current IMU data to the arduino over the i2c bus
	void init(); //this will initialize the i2c bus for the arduino.
	void getdata(scarborough::YPR& msg);
private:
	unsigned concat(unsigned x, unsigned y); //concatenates two unsigned numbers
	double imu_data[3];
	int orientation; //1=Y, 2=P, 3=R can't use zero
	int sign; //1 = negative 2 = positive
	long number[3];


};




#endif /* ARDUINO_I2C_H_ */
