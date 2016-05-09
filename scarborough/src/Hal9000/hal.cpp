/*
 * hal.cpp
 *
 *  Created on: Feb 25, 2016
 *      Author: sdcr
 */
#include "hal.h"

double imu_data[3];

void getdata(const scarborough::YPR& msg){
	for(int i=0;i<2;i++){
		//cout << "casting to double" << endl;
		imu_data[i] = boost::lexical_cast<double>(msg.YPR[i]);

	}

}

Hal::Hal(){
	//setup all variables here.
	desired_direction = n.advertise<scarborough::Desired_Directions>("HAL9000", 200);
	current_direction = n.subscribe<scarborough::YPR>("IMU_DATA", 200, getdata);
}

void Hal::init(){

}

void Hal::collection(){
	current_direction = n.subscribe<scarborough::YPR>("IMU_DATA", 200, getdata);


}

void Hal::process(){

}

void Hal::decide(){

}

void Hal::update_desired(int desired, int value){

	// publish desired directions to the desired chatter so that it can be pushed to the arduino by ardi2c
	directions.desired = desired;
	directions.value = value;
	desired_direction.publish(directions);

}





