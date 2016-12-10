/*
 * motors.cpp
 *
 *  Created on: Mar 9, 2016
 *      Author: sdcr
 */

#include "motors_scarborough.h"
#include "Helm.h" 
#include "I2Cdev.h"

I2Cdev i2cdev;
Motors_Scarborough motors;
Handler handler;
Helm helm;


/*
 * getdata is for ROS to collect variables from publishers
 */

bool killed;
scarborough::YPR _ypr;
scarborough::Depth _depth;
scarborough::Desired_Directions _desired;
void getdata(const scarborough::Motor_Speed& msg){

	//convert from boost int to c++ int
	//for(int i = 0; i < 6 ; i++){

	//	motors.motor_val[i] = msg.motor[i]; //boost::lexical_cast<int>(msg.motor[i]);

	//}
	//send values to class variable for further analysis

	//motors.motor_val[0] = 1000;
	//motors.motor_val[1] = 1000;
	

}
void getdata_kill(const scarborough::Kill_Switch& msg){

	killed = msg.killed;

}

void getdata_YPR(const scarborough::YPR& msg){
	_ypr = msg;
	

}

void getdata_DEPTH(const scarborough::Depth& msg){
	//_depth = msg;
	_depth.depth = -1.5;
}

void getdara_DESIRED(const scarborough::Desired_Directions& msg){
	//_desired = msg;
	_desired.depth = 4.0;
	_desired.throttle = 0;
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

	motors.init();
	helm.init();
	//main loop
	bool restart = true;
	while(ros::ok()){


	
		//if the kill switch is off do not send motor signals
		if(!killed){
			cout << "Get Data for PID" << endl;
			if(restart){
				 motors.kill_motors();
				 helm.reset();

				_desired.depth = 4.0;
				_desired.throttle = 0;
				_desired.rotation[0] = _ypr.YPR[0];
				_desired.rotation[1] = _ypr.YPR[1];
				_desired.rotation[2] = _ypr.YPR[2];
				restart = false;
				helm.update_desired(_desired);
			}

			
			helm.update_YPR(_ypr);
			helm.update_depth(_depth);
			//add in hard codes for desired

			

			
			helm.update_helm();
			helm.computron();
			motors.get_motor_values(helm.motor_output);
			motors.set_motor_speed();
			
			
		}
		else{
			cout << "killing motors" << endl;
			if(!restart){
				restart = true;
			}
			//wait here while off
			motors.kill_motors();

		}


		ros::spinOnce();
	}
}


void Motors_Scarborough::init(){

	//set killswitch to true until it gets updated
	motors.killer = true;


}

/*
 * Set motor speed will write the motor values to their individual motors over i2c
 */
void Motors_Scarborough::set_motor_speed(){
	i2cdev.writeWord(0x04, (uint8_t)0, (uint16_t)input.motor[0]); //motor1
	i2cdev.writeWord(0x04, (uint8_t)1, (uint16_t)input.motor[1] ); // motor2
	i2cdev.writeWord(0x04, (uint8_t)2, (uint16_t)input.motor[2] ); // motor3
	i2cdev.writeWord(0x04, (uint8_t)3, (uint16_t)input.motor[3] ); // motor4
	i2cdev.writeWord(0x04, (uint8_t)4, (uint16_t)input.motor[4] ); //motor 5
	i2cdev.writeWord(0x04, (uint8_t)5, (uint16_t)input.motor[5] ); //motor 6
}

/*
 * Get motor values will grab the motor values from the ROS system and set them to some class variables
 */
void Motors_Scarborough::get_motor_values(scarborough::Motor_Speed _input){
	input = _input;
}

int Motors_Scarborough::i2cConvert(int address){

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

bool Motors_Scarborough::check_kill_switch(){

	return killer;

}

void Motors_Scarborough::kill_motors(){
	i2cdev.writeWord(0x04, 0, (uint16_t)1500); //motor1
	i2cdev.writeWord(0x04, 1, (uint16_t)1500 ); // motor2
	i2cdev.writeWord(0x04, 2, (uint16_t)1500 ); // motor3
	i2cdev.writeWord(0x04, 3, (uint16_t)1500 ); // motor4
	i2cdev.writeWord(0x04, 4, (uint16_t)1500 ); //motor 5
	i2cdev.writeWord(0x04, 5, (uint16_t)1500 ); //motor 6
}


