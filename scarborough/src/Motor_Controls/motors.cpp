/*
 * motors.cpp
 *
 *  Created on: Mar 9, 2016
 *      Author: sdcr
 */

#include "motors.h"

I2Cdev i2cdev;
Motors motors;
Handler handler;



/*
 * getdata is for ROS to collect variables from publishers
 */
void getdata(const scarborough::Motor_Speed& msg){

	//convert from boost int to c++ int
	for(int i = 0; i < 6 ; i++){

		motors.motor_val[i] = msg.motor[i]; //boost::lexical_cast<int>(msg.motor[i]);

	}
	//send values to class variable for further analysis

}
void getdata_kill(const scarborough::Kill_Switch& msg){

	motors.killer = msg.killed;

}

int main(int argc, char **argv){

	//initialize ROS
	ros::init(argc, argv, handler.MOTOR_CHATTER);

	//Make node handler
	ros::NodeHandle motor_handle;
	ros::Subscriber motor_subscriber = motor_handle.subscribe(handler.MOTORS, 200, getdata);
	ros::Subscriber kill_Switch = motor_handle.subscribe(handler.KILL, 200, getdata_kill);
	motors.init();

	//main loop
	while(ros::ok()){



		//if the kill switch is off do not send motor signals
		if(!motors.killer){

			motors.set_motor_speed();
			cout << motors.motor_val << endl;
		}
		else{
			cout << "killing motors" << endl;
			motors.kill_motors();

		}


		ros::spinOnce();
	}
}


void Motors::init(){

	//set killswitch to true until it gets updated
	motors.killer = true;


}

/*
 * Set motor speed will write the motor values to their individual motors over i2c
 *
 * motor addresses will be:
 * bus: 1
 * M1: 39 Left
 * M2: 35 Right
 * M3: 36 Right Front
 * M4: 37 Left Front
 * M5: 38 Left Back
 * M6: 34 Right Back
 */
void Motors::set_motor_speed(){


	i2cdev.writeWord(0x39, 0, (uint16_t)motor_val[0] ); //motor1
	i2cdev.writeWord(0x35, 0, (uint16_t)motor_val[1] ); // motor2
	i2cdev.writeWord(0x36, 0, (uint16_t)motor_val[2] ); // motor3
	i2cdev.writeWord(0x37, 0, (uint16_t)motor_val[3] ); // motor4
	i2cdev.writeWord(0x38, 0, (uint16_t)motor_val[4] ); //motor 5
	i2cdev.writeWord(0x34, 0, (uint16_t)motor_val[5] ); //motor 6
}

/*
 * Get motor values will grab the motor values from the ROS system and set them to some class variables
 */
void Motors::get_motor_values(int motor_raw[6]){
	for(int i = 0 ; i < 6 ; i++){

		//TODO Matt Pedler: do an actual conversion of what needs to be written. For right now this will suffice
		motor_val[i] = (int)motor_raw[i];
	}
}

int Motors::i2cConvert(int address){

	//load int into string stream
	stringstream ss;
	ss << address;
	string ss_return;
	//load ss into string
	ss >> ss_return;

	int length;

	//get length of the string
	length = ss_return.length();
	int temp = 0;
	int _length = length;

	//this will convert the number from hex to decimal
	//this only works for hex numbers that do not contain a letter in them.

	for(int i = 0; i < length ;i++){

		//add a modifier based upon where it is at in the string
		int moder = (16 * (_length -1));
		//if the modifier is zero make it 1
		moder = max(moder, 1);

		//convert the string from the hex number to the decimal int
		temp += atoi(ss_return.substr(i,1).c_str()) * moder;
		_length--;

		//cout << temp << " / " << atoi(ss_return.substr(i,1).c_str())  << " / " << moder<< endl;

	}
	//return the decimal int number we can use to access the device on the i2c
	return temp;

}

bool Motors::check_kill_switch(){

	return killer;

}

void Motors::kill_motors(){
	i2cdev.writeWord(0x39, 0, (uint16_t)0 ); //motor1
	i2cdev.writeWord(0x35, 0, (uint16_t)0 ); // motor2
	i2cdev.writeWord(0x36, 0, (uint16_t)0 ); // motor3
	i2cdev.writeWord(0x37, 0, (uint16_t)0 ); // motor4
	i2cdev.writeWord(0x38, 0, (uint16_t)0 ); //motor 5
	i2cdev.writeWord(0x34, 0, (uint16_t)0 ); //motor 6
}


