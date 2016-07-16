/*
 * Heimdall_main.cpp
 *
 *  Created on: Jul 16, 2016
 *      Author: ximidar
 */

#include "Heimdall.h"


Handler scarborough_handler;
Heimdall vision;
int main(int argc, char **argv){

	ros::init(argc, argv, scarborough_handler.HEMDALL_CHATTER);

	ros::NodeHandle n;

	ros::Publisher vision_pub = n.advertise<scarborough::Vision_objects>(scarborough_handler.CV_MESSAGES, 200);

	//initialize cameras
	if(!vision.init()){
		return -1;
	}

	while(ros::ok()){
		vision.heimdall_bouy(vision.HIDE_VIDEO);
		vision_pub.publish(vision.bouy);


		//find path markers
		vision_pub.publish(vision.path_marker);


		//find gates
		vision_pub.publish(vision.gate);

	}



}


