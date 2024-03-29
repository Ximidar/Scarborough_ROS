/*
 * anchor.h
 *
 *  Created on: May 30, 2016
 *      Author: sdcr
 *
*    This is made with reference to Blue Robotics Github page. Almost none of this program is original content
*    Here's the reference: https://github.com/bluerobotics/BlueRobotics_MS5837_Library
 */

#ifndef SRC_DEPTH_SENSOR_ANCHOR_H_
#define SRC_DEPTH_SENSOR_ANCHOR_H_

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

class Anchor{

public:
	//blue robotics variables
	static const float Pa = 100.0f;
	static const float bar = 0.001f;
	static const float mbar = 1.0f;

	void setFluidDensity(float density);
	void read();
	void readTestCase();
	float temperature();
	float depth();
	float altitude();
	float pressure(float conversion = 1.0f);
	void init();
	//void Anchor();

private:
	uint16_t C[8];
	uint32_t D1, D2;
	int TEMP;
	int P;

	float fluidDensity;

	void calculate();

	uint8_t crc4(uint16_t n_prom[]);



};



#endif /* SRC_DEPTH_SENSOR_ANCHOR_H_ */
