/*
 * motors.cpp
 *
 *  Created on: Mar 9, 2016
 *      Author: sdcr
 */

#include "motors.h"

I2Cdev i2cdev;
motors motors;


void getdata(const scarborough::Motor_Speed& msg){

	motors.get_motor_values(boost::lexical_cast<double>(msg.motor));

}

int main(int argc, char **argv){
	ros::init(argc, argv, "MOTORS");
	ros::NodeHandle motor_handle;

	while(ros::ok()){

		motor_handle.subscribe("ARD_I2C", 200, getdata);
		motors.set_motor_speed();

		ros::spinOnce();
	}
}

void motors::init(){
	//always good to have an init function for future proofing
}

/*
 * Set motor speed will write the motor values to their individual motors over i2c
 *
 * motor addresses will be:
 *
 * M1: 51
 * M2: 52
 * M3: 53
 * M4: 54
 * M5: 55
 * M6: 56
 */
void motors::set_motor_speed(){
	for(int i = 0 ; i < sizeof(motor_val) ; i++){
		//write number to the motor over i2c
		i2cdev.writeWord(i+51, 0, (uint16_t)motor_val[i] );
	}
}

/*
 * Get motor values will grab the motor values from the ROS system and set them to some class variables
 */
void motors::get_motor_values(double motor_raw[6]){
	for(int i = 0 ; i < sizeof(motor_val) ; i++){

		//TODO Matt Pedler: do an actual conversion of what needs to be written. For right now this will suffice
		motor_val[i] = (int)motor_raw[i];
	}
}

