/*
 * arduino_i2c.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: sdcr
 */
#include "arduino_i2c.h"

I2Cdev i2c;

ArdI2C::ArdI2C(){
	orientation = 0;
}
//this will initialize the i2c bus for the arduino.
void ArdI2c::init(){
	//initialize class variables
	imu_data = {0,0,0};
	orientation = 0;
	sign = 0;
	number = {0,0,0};
}
// This will query the correct ROS stream to get the IMU data
void ArdI2C::get_accel_info(){
	ros::NodeHandle IMU;
	ros::Subscriber imu = IMU.subscribe("IMU_DATA", 200, getdata);

}
//write a value to the arduino over the i2c bus
/*
 * number should look like 12456789
 * first number indicates orientation 1=Y 2=P 3=R
 * Second number indicates positive or negative number 1=positive 2 = negative
 * rest of the numbers indicate the number we intend to send with three decimal points
 */
void ArdI2C::ardWrite(){
	get_accel_info();
	for(int i = 0; i < 2 ; i++){
		orientation = i + 1; // set correct orientation

		//check if number is below 0 if so then change to positive
		if(imu_data[i] < 0){
			sign = 1;
			imu_data[i] = fabs(imu_data[i]);
		}
		else{
			sign = 2;
		}

		// change number from ###.######### format to ###.###. if we have an 8.9872354 it would be 8987
		number[i] = imu_data[i] * 1000 - (imu_data * 1000 %1);

		//concatenate all the numbers into the final number.
		number[i] = concat(orientation,concat(sign,number[i]);

		//TODO this is where we would write the long number to the i2c bus
		i2c.writeBytes(ARDUINO_DEV_ADDR, ARDUINO_REG_ADDR, ARDUINO_LENGTH, number[i]);
	}
}


unsigned ArdI2C::concat(unsigned x, unsigned y){
	unsigned power = 10;
	while(y>= power){
		power *= 10;
	}
	return x * power + y;
}
void ArdI2C::getdata(scarborough::YPR& msg){
	for(int i=0;i<2;i++){
		imu_data[i] = msg.YPR[i];
	}

}





