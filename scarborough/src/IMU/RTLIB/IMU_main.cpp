#include "ros/ros.h"
#include "std_msgs/String.h"
#include "scarborough/YPR.h"
#include "scarborough/Kill_Switch.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include "../../HandlerNames/HANDLER_NAMES.h"
#include "IMU2.h"
bool killer = false;


void getdata_KILL(const scarborough::Kill_Switch& msg){
	killer = msg.killed;

}

Handler handler;

int main(int argc, char **argv) {
	cout << "initializing ROS" << endl;
	ros::init(argc, argv, handler.IMU_CHATTER);

	ros::NodeHandle n;
	ros::NodeHandle kill;
	ros::Subscriber sub;

	

	ros::Publisher imu_pub = n.advertise<scarborough::YPR>(handler.IMU, 200);
    sub = kill.subscribe(handler.KILL, 20, getdata_KILL);

    IMU2 imu2;

    while(ros::ok()){
    	if(imu2.Ok()){
    		imu2.get_imu();

    		imu_pub.publish(imu2.ypr_ROS);
		}


			ros::spinOnce();
			

    }




}
