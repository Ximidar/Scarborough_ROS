/*
 * HANDLER_NAMES.h
 *
 *  Created on: Jul 9, 2016
 *      Author: ximidar
 */

#ifndef SRC_HANDLERNAMES_HANDLER_NAMES_H_
#define SRC_HANDLERNAMES_HANDLER_NAMES_H_

#include <string>
#include <iostream>

using namespace std;

class Handler{
public:
	//message names
	const string IMU = "IMU";
	const string DEPTH_SENSOR = "DEPTH";
	const string KILL = "KILL";
	const string MOTORS = "MOTORS";
	const string DESIRED = "DESIRED";
	const string HAL = "HAL";
	//chatter names
	const string ARD_I2C_CHATTER = "ARD_I2C_CHATTER";
	const string IMU_CHATTER = "IMU_CHATTER";
	const string MOTOR_CHATTER = "MOTOR_CHATTER";
	const string HAL_CHATTER = "HAL_CHATTER";

};


#endif /* SRC_HANDLERNAMES_HANDLER_NAMES_H_ */
