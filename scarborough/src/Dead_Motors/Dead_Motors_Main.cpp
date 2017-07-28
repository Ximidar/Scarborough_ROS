#include "I2Cdev.h"
#include <iostream>
#include "scarborough/Motor_Speed.h"
#include "scarborough/Kill_Switch.h"
#include "../HandlerNames/HANDLER_NAMES.h"
#include "ros/ros.h"
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <unistd.h>
#include "Dead_Motors.h"

I2Cdev i2cdev;
Handler handler;
Dead_Motors dm;

/*
 * getdata is for ROS to collect variables from publishers
 */

bool killed;
scarborough::YPR _ypr;
scarborough::Depth _depth;
scarborough::Desired_Directions _desired;
double fake_depth = 0;
bool depth_reached = false;

using namespace std;

void getdata_kill(const scarborough::Kill_Switch& msg){

	killed = msg.killed;

}

void getdata_YPR(const scarborough::YPR& msg){
	_ypr = msg;
	

}

void getdata_DEPTH(const scarborough::Depth& msg){
	_depth = msg;
	
	//_depth.depth = fake_depth;
}

void getdara_DESIRED(const scarborough::Desired_Directions& msg){
	//_desired = msg;
	_desired.depth = 4.0;
	_desired.throttle = 0;
}





/*
 * Set motor speed will write the motor values to their individual motors over i2c
 */
void set_motor_speed(){
	i2cdev.writeWord(0x04, (uint8_t)10, (uint16_t)dm.motor_output.motor[0]); //motor1
	i2cdev.writeWord(0x04, (uint8_t)11, (uint16_t)dm.motor_output.motor[1] ); // motor2
	i2cdev.writeWord(0x04, (uint8_t)12, (uint16_t)dm.motor_output.motor[2] ); // motor3
	i2cdev.writeWord(0x04, (uint8_t)13, (uint16_t)dm.motor_output.motor[3] ); // motor4
	i2cdev.writeWord(0x04, (uint8_t)14, (uint16_t)dm.motor_output.motor[4] ); //motor 5
	i2cdev.writeWord(0x04, (uint8_t)15, (uint16_t)dm.motor_output.motor[5] ); //motor 6

	cout<< dm.motor_output << endl;

	
	cout << endl;
}

void kill_motors(){
	i2cdev.writeWord(0x04, 10, (uint16_t)1500); //motor1
	i2cdev.writeWord(0x04, 11, (uint16_t)1500 ); // motor2
	i2cdev.writeWord(0x04, 12, (uint16_t)1500 ); // motor3
	i2cdev.writeWord(0x04, 13, (uint16_t)1500 ); // motor4
	i2cdev.writeWord(0x04, 14, (uint16_t)1500 ); //motor 5
	i2cdev.writeWord(0x04, 15, (uint16_t)1500 ); //motor 6
}



int main(int argc, char **argv){

	//initialize ROS
	ros::init(argc, argv, handler.MOTOR_CHATTER);

	//Make node handler
	ros::NodeHandle motor_handle;
	ros::NodeHandle n;
	//ros::Subscriber motor_subscriber = motor_handle.subscribe(handler.MOTORS, 20, getdata);
	ros::Subscriber kill_Switch = motor_handle.subscribe(handler.KILL, 20, getdata_kill);
	ros::Subscriber YPR_in = n.subscribe(handler.IMU, 200, getdata_YPR);
	ros::Subscriber depth_in = n.subscribe(handler.DEPTH_SENSOR, 200, getdata_DEPTH);

	//main loop
	bool restart = true;
	while(ros::ok()){


	
		//if the kill switch is off do not send motor signals
		if(killed == 1){
			if(restart){
				kill_motors();
				

				_desired.depth = 4.0;
				_desired.throttle = 0;
				_desired.rotation[0] = _ypr.YPR[0];
				_desired.rotation[1] = _ypr.YPR[1];
				_desired.rotation[2] = _ypr.YPR[2];
				_desired.mode = "NORMAL_OP";
				restart = false;
				cout << "Sleeping for 5 seconds" << endl;
				kill_motors();
				sleep(5);
				kill_motors();
				cout << "End Sleep" << endl;
				depth_reached = false;
				
			}
			sleep(0.1);
			//fake_depth += 0.1;
			cout << _depth;
			if(_depth.depth < _desired.depth && !depth_reached){
				dm.dive(_depth, _ypr, _desired);

			}
			else{
				depth_reached = true;
				dm.keep_heading(_depth, _ypr, _desired);
			}
			set_motor_speed();
			
			
		}
		else{
			if(!restart){
				restart = true;
				cout << "killing motors" << endl;
			}
			//wait here while off
			kill_motors();

		}


		ros::spinOnce();
	}
	kill_motors();

}

