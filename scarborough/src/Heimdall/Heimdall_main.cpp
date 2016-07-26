/*
 * Heimdall_main.cpp
 *
 *  Created on: Jul 16, 2016
 *      Author: ximidar
 */

#include "Heimdall.h"
double current_depth;
string current_state;
Handler scarborough_handler;
Heimdall vision;
VISION_OBJECTS objects;


void getdata_DEPTH(const scarborough::Depth& msg){
	current_depth = msg.depth;
}

void getdata_state(const scarborough::Hal& msg){
	current_state = string(msg.state);
}



int main(int argc, char **argv){

	ros::init(argc, argv, scarborough_handler.HEMDALL_CHATTER);

	ros::NodeHandle n;

	ros::Publisher vision_pub = n.advertise<scarborough::Vision_objects>(scarborough_handler.CV_MESSAGES, 200);

	ros::Subscriber depth_sub = n.subscribe(scarborough_handler.DEPTH_SENSOR, 200, getdata_DEPTH);


	//initialize cameras
	if(!vision.init()){
		return -1;
	}

	while(ros::ok()){

//		vision.forward >> vision.src ;
//		vision.downward >> vision.down;

		vision.test_camera();

//		vision.get_state(current_state);
//		vision.get_depth(current_depth);
//
//		// find the path markers
//	//	if( vision.state == "PATH"){
//		vision.heimdall_pathmarker(vision.HIDE_VIDEO);
//		vision_pub.publish(vision.path_marker );
//		//}
//
//		//if( vision.state == "BOUY"){
//		vision.heimdall_bouy(vision.HIDE_VIDEO);
//		vision_pub.publish(vision.red_bouy);
//	//}
//
		//find gates
		//vision_pub.publish(vision.gate);

	//	ros::spinOnce();

	}



}


