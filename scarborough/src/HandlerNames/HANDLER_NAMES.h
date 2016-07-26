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
	//Alex 2016-07-25: changed from in-class initialization to an initializer list in the constructor
	const string IMU;
	const string DEPTH_SENSOR;
	const string KILL;
	const string MOTORS;
	const string DESIRED;
	const string HAL;
	const string CV_MESSAGES;
	//chatter names
	const string HEMDALL_CHATTER; //TODO: rename HEMDALL_CHATTER to HEIMDALL_CHATTER
	const string ARD_I2C_CHATTER;
	const string IMU_CHATTER;
	const string MOTOR_CHATTER;
	const string HAL_CHATTER;

	Handler()
	: IMU("IMU"), DEPTH_SENSOR("DEPTH_SENSOR"), KILL("KILL"),
	  MOTORS("MOTORS"), DESIRED("DESIRED"), HAL("HAL"),
	  CV_MESSAGES("CV_MESSAGES"), HEMDALL_CHATTER("HEIMDALL_CHATTER"), ARD_I2C_CHATTER("ARD_I2C_CHATTER"),
	  IMU_CHATTER("IMU_CHATTER"), MOTOR_CHATTER("MOTOR_CHATTER"), HAL_CHATTER("HAL_CHATTER")
	  {}

};


#endif /* SRC_HANDLERNAMES_HANDLER_NAMES_H_ */
