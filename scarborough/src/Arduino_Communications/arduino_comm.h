/*
 * arduino_comm.h
 *
 *  Created on: Jan 24, 2016
 *      Author: sdcr
 */

#ifndef ARDUINO_COMM_H_
#define ARDUINO_COMM_H_
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "scarborough/Motor_Speed.h"
#include "scarborough/YPR.h"
#include <sstream>
#include <iostream>
#include <string>
#include <SerialStream.h> //http://libserial.sourceforge.net/
#include <sys/stat.h> //this is for checking for certain files IE: use it for checking the /dev folder for available comm ports
#include <boost/lexical_cast.hpp> //used to cast from number to string
#include "arduino_i2c.h"


using namespace std;
using namespace LibSerial;


class ArdComm{
	public:
		string listen();
		std_msgs::String msg;
		scarborough::Motor_Speed motor;
		void init(); //initialize comm port not used currently since i2c communication works
		ArdComm();
		void interperet_message(string message);
		inline bool pathExists (const std::string& name);


	private:

		//init variables
		bool handshake;
		string path;

		//listen
		int message_count;

		//Interpret message
		string message;
		string delimiter;
		string parse;
		unsigned int pos;


};


#endif /* ARDUINO_COMM_H_ */
