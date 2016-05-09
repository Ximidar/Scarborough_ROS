/*
 * arduino_i2c.h
 *
 *  Created on: Feb 1, 2016
 *      Author: sdcr
 */

#ifndef ARDUINO_I2C_H_
#define ARDUINO_I2C_H_

//definitions for I2Cdev
#define ARDUINO_DEV_ADDR 0x04

//definitions for PID control aggression
#define AGRESSIVE 0
#define MEDIUM 1
#define FINE 2

//definitions for updating desired
#define YAW 0
#define DEPTH 1


#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "I2Cdev.h"
#include "scarborough/YPR.h"
#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>

using namespace std;

class ArdI2C{
public:
	ArdI2C();
	void get_accel_info(); // This will query the correct ROS stream to get the IMU data
	void ardWrite(double imu_data[3]); //write the current IMU data to the arduino over the i2c bus
	string ardRead();
	void init(); //this will initialize the i2c bus for the arduino.
	void update_desired(int type, int value);
	void pid_Control(int motor, int mode);
	void pid_monitor();

private:
	unsigned long concat(unsigned long x, unsigned long y); //concatenates two unsigned numbers

	int orientation; //1=Y, 2=P, 3=R can't use zero
	int sign; //1 = negative 2 = positive

	int final_reference[2];
	int desired_yaw;
	int desired_depth;

	//read from arduino variables
	uint8_t m1[30];
	uint8_t m2[30];
	uint8_t m3[30];
	uint8_t m4[30];
	uint8_t m5[30];
	uint8_t m6[30];
	uint8_t delim;
	string m1s, m2s ,m3s, m4s, m5s, m6s;
	string arduino_message;


};




#endif /* ARDUINO_I2C_H_ */
