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
double depth;
void getdata_YPR(const scarborough::YPR& msg){
	for(int i=0;i<2;i++){
		//cout << "casting to double" << endl;
		imu_data[i] = boost::lexical_cast<double>(msg.YPR[i]);

	}

}


void getdata_KILL(const scarborough::Kill_Switch& msg){

	killer = msg.killed;

}

void getdata_DEPTH(const scarborough::Depth& msg){
	depth = msg.depth;
}

////////////////////////////////////MAIN CODE///////////////////////////////

Hal hal;
Handler scarborough_handler;

int main(int argc, char **argv){

	ros::init(argc, argv, scarborough_handler.HAL_CHATTER);

	while(ros::ok()){
		hal.set_killer(killer);

		if(!hal.killed){
			hal.state_loop(hal.current_state);
		}
		else{
			hal.update_state(hal.RESET);
			hal.state_loop(hal.current_state);
		}


	}

}

