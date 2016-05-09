/*
 * motors.cpp
 *
 *  Created on: Mar 9, 2016
 *      Author: sdcr
 */

#include "motors.h"

I2Cdev i2cdev;
Motors motors;


/*
 * getdata is for ROS to collect variables from publishers
 */
void getdata(const scarborough::Motor_Speed& msg){
	//variable for temporary storage of motor values
	double motor_temp[6];

	//convert from boost double to c++ double
	for(int i = 0; i < 6 ; i++){
		motor_temp[i] = boost::lexical_cast<double>(msg.motor[i]);
	}
	//send values to class variable for further analysis
	motors.get_motor_values(motor_temp);
}

int main(int argc, char **argv){

	//initialize ROS
	ros::init(argc, argv, "MOTORS");

	//Make node handler
	ros::NodeHandle motor_handle;

	//main loop
	while(ros::ok()){


		motor_handle.subscribe("ARD_I2C", 200, getdata);
		motors.set_motor_speed();

		ros::spinOnce();
	}
}

/*
 * init should be used for braking here until the killswitch is pushed
 */
void Motors::init(){

}

/*
 * Set motor speed will write the motor values to their individual motors over i2c
 *
 * motor addresses will be:
 * bus: 1
 * M1: 51
 * M2: 52
 * M3: 53
 * M4: 54
 * M5: 55
 * M6: 56
 */
void Motors::set_motor_speed(){
	for(int i = 0 ; i < 6 ; i++){
		//write number to the motor over i2c
		i2cdev.writeWord(i+51, 0, (uint16_t)motor_val[i] );
	}
}

/*
 * Get motor values will grab the motor values from the ROS system and set them to some class variables
 */
void Motors::get_motor_values(double motor_raw[6]){
	for(int i = 0 ; i < 6 ; i++){

		//TODO Matt Pedler: do an actual conversion of what needs to be written. For right now this will suffice
		motor_val[i] = (int)motor_raw[i];
	}
}


