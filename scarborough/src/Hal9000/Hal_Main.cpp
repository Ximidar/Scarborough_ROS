/*
 * Hal_Main.cpp

 *
 *  Created on: Jul 11, 2016
 *      Author: ximidar
 */
#include "hal.h"


////////////////////////////////ROS MESSAGES/////////////////////////
double imu_data[3];
bool killer;
double current_depth;
scarborough::Vision_objects vision_mes;

void getdata_YPR(const scarborough::YPR& msg){
	for(int i=0;i<3;i++){
		//cout << "casting to double" << endl;
		imu_data[i] = boost::lexical_cast<double>(msg.YPR[i]);


	}
	

}


void getdata_KILL(const scarborough::Kill_Switch& msg){

	killer = msg.killed;
	//cout << "Killer: " << killer << endl;

}

void getdata_DEPTH(const scarborough::Depth& msg){
	current_depth = msg.depth;
}

void getdata_VISION(const scarborough::Vision_objects& msg){
	vision_mes = msg;
}


////////////////////////////////////MAIN CODE///////////////////////////////

Hal hal;
Handler scarborough_handler;

int main(int argc, char **argv){

	ros::init(argc, argv, scarborough_handler.HAL_CHATTER);
	
	ros::NodeHandle n;

	ros::Subscriber vision ;
	ros::Subscriber kill ;
	ros::Subscriber depth ;
	ros::Subscriber curYPR ;


	ros::Publisher  pub =  n.advertise<scarborough::Hal>(scarborough_handler.HAL, 200);
	ros::Publisher desired_direction = n.advertise<scarborough::Desired_Directions>(scarborough_handler.DESIRED, 200);
	kill = n.subscribe(scarborough_handler.KILL, 200, getdata_KILL);
	curYPR = n.subscribe(scarborough_handler.IMU, 200, getdata_YPR);
	depth = n.subscribe(scarborough_handler.DEPTH_SENSOR, 200, getdata_DEPTH);
	//vision = n4.subscribe(scarborough_handler.CV_MESSAGES, 200, getdata_VISION);
	
	hal.set_killer(killer);
	hal.set_rot(imu_data);
	hal.set_vision(vision_mes);
	hal.set_depth(current_depth);

	hal.init();

	while(ros::ok()){



		hal.set_killer(killer);
		hal.set_rot(imu_data);
		hal.set_depth(current_depth);

		if(hal.killed == 1){
			hal.state_loop(hal.current_state);
			pub.publish(hal.state_check);
			desired_direction.publish(hal.desired); //Alex 2016-07-25: this replaces Hal::update_desired
			//are there any situations where the desired direction in hal are changed but shouldn't be published?
			cout << hal.desired << endl;
			
		}
		else{
			hal.update_state(hal.RESET);
			hal.state_loop(hal.current_state);
		}

		ros::spinOnce();
	}

}

