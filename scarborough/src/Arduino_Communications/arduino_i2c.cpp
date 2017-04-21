/*
 * arduino_i2c.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: sdcr
 */
#include "arduino_i2c.h"
#include "arduino_comm.h"

I2Cdev i2cdev;

ArdI2C i2c;
ArdComm ardcomm;
Handler handler;

double imu_data[3];

scarborough::Desired_Directions desired_directions;

/*
 * This function takes the data from the IMU_DATA publisher and throws it into a double that we can use.
 */
void getdata(const scarborough::YPR& msg){
	for(int i=0;i<2;i++){
		//cout << "casting to double" << endl;
		imu_data[i] = boost::lexical_cast<double>(msg.YPR[i]);

	}

}



void getdata_DESIRED(const scarborough::Desired_Directions& msg){

	desired_directions = msg;

}

//Main function for ArdI2C executable
int main(int argc, char **argv){

	ros::init(argc, argv, handler.ARD_I2C_CHATTER);
	ros::NodeHandle IMU;
	ros::NodeHandle n;

	ros::Subscriber imu;
	ros::Publisher ard_pub = n.advertise<scarborough::Motor_Speed>(handler.MOTORS, 100);
	ros::Publisher depth_pub = n.advertise<scarborough::Depth>(handler.DEPTH_SENSOR, 100);
	ros::Publisher kill_pub = n.advertise<scarborough::Kill_Switch>(handler.KILL, 10);

	ros::Subscriber sub;

	i2c.init(); // does nothing.

	imu = IMU.subscribe(handler.IMU, 200, getdata);
	sub = n.subscribe(handler.DESIRED, 200, getdata_DESIRED);
	string kill_string = "";
	string depth_string = "";


	while(ros::ok()){

		//read message from arduino and parse it
		
		//try to interperet message
		kill_string = i2c.read_kill();
		depth_string = i2c.read_depth();

		ardcomm.interperet_message(kill_string);
		ardcomm.interperet_message(depth_string);

		//publish motor data to the ARD_I2C
		//ard_pub.publish(ardcomm.motor);
		depth_pub.publish(ardcomm.depth);
		kill_pub.publish(ardcomm.kill_switch);
		
		//cout << ardcomm.motor << endl;
		cout << ardcomm.depth << endl;
		cout << ardcomm.kill_switch << endl;
		
		

		ros::spinOnce();
	}



}


ArdI2C::ArdI2C(){
	orientation = 0;
	sign = 0;
	delim = 0; //On the arduino this delimiter should be 255 on teensy it is 0
	desired_yaw = 0;
	desired_depth = 4;

}
//use this if ever needed... It used to do something but is now a ghost of algorithms past
void ArdI2C::init(){

	//write the pid values to the teensy
	//pid_Set();


}

/*
 * ardRead grabs the current motor speed from the arduino in a string and returns the string.
 * this data will contain the motor speeds that the PID puts out. the "delim" variable is a
 * uint8_t variable that equals 255. this is used to end the string at the correct place. If the returned
 * string is over 128 characters we will need to expand the final variable.
 *
 * The readBytes function needs an address register length and a uint8_t array
 * certain registers will return certain values. We cant pull every value at once
 * but we can pull the values over a few i2c reads then load all the variables into
 * a string and send it on its way. register 51 - 56 will return the motor values.
 */
string ArdI2C::ardRead(){

	string ks, ds;
	string arduino_message;

	//read from arduino variables
	uint8_t k[20];
	uint8_t d[20];

	//read all registeries from the arduino
	i2cdev.readBytes(0x04, 57, 20, k);
	i2cdev.readBytes(0x04, 58, 20, d);

	//make all variable strings be nothing.
	arduino_message = "";
	 ks = "";
	 ds = "";


	//load all strings with variables from the arduino read.
	for(int j = 0; j<20;j++){
		
		if(k[j] != delim){
			ks += k[j];
		}
		if(d[j] != delim){
			ds += d[j];
		}
	}

	//load all individual strings into one big string

	arduino_message = ks + ds;

	//output to console for debug purposes.
	return arduino_message;
}

string ArdI2C::read_kill(){
	string kill_s;
	uint8_t k_char[20];
	kill_s = "";
	try{
		i2cdev.readBytes(0x04, 57, 20, k_char);
	}
	catch(int e){
		cout << "I2C Read error"<< endl;
		return kill_s;
	}	
	for(int j = 0; j<20;j++){
		
		if(k_char[j] != delim){
			kill_s += k_char[j];
		}
	}
	return kill_s;

}

string ArdI2C::read_depth(){
	string ds;
	uint8_t d[20];
	ds = "";
	try{
		i2cdev.readBytes(0x04, 58, 20, d);
	}
	catch(int e){
		cout << "I2C Read error"<< endl;
		return ds;
	}
	
	
	for(int j = 0; j<20;j++){
		
		if(d[j] != delim){
			ds += d[j];
		}
	}
	return ds;

}


/*
 * yaw 9
 * pitch 10
 * roll 11
 * depth 12
 * throttle 13
 *
 */
void ArdI2C::update_desired(scarborough::Desired_Directions _desired){

	//write desired YPR

	int desiredYPR[3];

	for (int i = 0 ; i < 3 ; i++){
		desiredYPR[i] = (int)_desired.rotation[i];
	}

	for (int i = 0 ; i < 3 ; i++){
	i2cdev.writeWord(4 , (uint8_t)9+i,(uint16_t)desiredYPR[i]);
	}

	//update depth
	i2cdev.writeWord(4 , (uint8_t)12,(uint16_t) _desired.depth);

	//update throttle
	i2cdev.writeWord(4 , (uint8_t)13, (uint16_t) _desired.throttle);

	cout << _desired << endl;


}

//reg 15 - 38
void ArdI2C::pid_Set(){
	cout<<"Initializing pid values" <<endl;
	
	double yaw_pid[3] = {4.0 ,1.0, 1.0};

	double pitch_pid[3] = {4.0 ,1.0, 1.0};

	double roll_pid[3]  = {4.0 ,1.0, 1.0};

	double depth_pid[3] = {4.0 ,1.0, 1.0};

	//final_pid_reference = {15,15};
	//write the yaw PID values
	for( int i = 0 ; i < 3 ; i++ ){
		//takes first part of the number IE: 123.456 turns into 123
		final_pid_reference[0] = yaw_pid[i] - (fmod(yaw_pid[i], 1));

		//takes second part of number IE: 123.456 turns into 456
		final_pid_reference[1] = fmod(yaw_pid[i], 1) * 1000;

		//write both parts of the number to the i2c bus on different registers

		if(i == 0){
			i2cdev.writeWord(4 , (uint8_t)15 ,(uint16_t)final_pid_reference[0]);
			i2cdev.writeWord(4 , (uint8_t)16 ,(uint16_t)final_pid_reference[1]);
		}
		else if(i == 1){
			i2cdev.writeWord(4 , (uint8_t)17 ,(uint16_t)final_pid_reference[0]);
			i2cdev.writeWord(4 , (uint8_t)18 ,(uint16_t)final_pid_reference[1]);
		}
		else if(i == 2){
			i2cdev.writeWord(4 , (uint8_t)19 ,(uint16_t)final_pid_reference[0]);
			i2cdev.writeWord(4 , (uint8_t)20 ,(uint16_t)final_pid_reference[1]);
		}
		
	}

	//write the pitch PID values
	for( int i = 0 ; i < 3 ; i++ ){
		//takes first part of the number IE: 123.456 turns into 123
		final_pid_reference[0] = pitch_pid[i] - (fmod(pitch_pid[i], 1));

		//takes second part of number IE: 123.456 turns into 456
		final_pid_reference[1] = fmod(pitch_pid[i], 1) * 1000;

		//write both parts of the number to the i2c bus on different registers
		//rawr im a comment
		if(i == 0){
			i2cdev.writeWord(4 , (uint8_t)21 ,(uint16_t)final_pid_reference[0]);
			i2cdev.writeWord(4 , (uint8_t)22 ,(uint16_t)final_pid_reference[1]);
		}
		else if(i == 1){
			i2cdev.writeWord(4 , (uint8_t)23 ,(uint16_t)final_pid_reference[0]);
			i2cdev.writeWord(4 , (uint8_t)24 ,(uint16_t)final_pid_reference[1]);
		}
		else if(i == 2){
			i2cdev.writeWord(4 , (uint8_t)25 ,(uint16_t)final_pid_reference[0]);
			i2cdev.writeWord(4 , (uint8_t)26 ,(uint16_t)final_pid_reference[1]);
		}
		
	}

	//write the Roll pid values
	for( int i = 0 ; i < 3 ; i++ ){
		//takes first part of the number IE: 123.456 turns into 123
		final_pid_reference[0] = roll_pid[i] - (fmod(roll_pid[i], 1));

		//takes second part of number IE: 123.456 turns into 456
		final_pid_reference[1] = fmod(roll_pid[i], 1) * 1000;

		//write both parts of the number to the i2c bus on different registers

		if(i == 0){
			i2cdev.writeWord(4 , (uint8_t)27 ,(uint16_t)final_pid_reference[0]);
			i2cdev.writeWord(4 , (uint8_t)28 ,(uint16_t)final_pid_reference[1]);
		}
		else if(i == 1){
			i2cdev.writeWord(4 , (uint8_t)29 ,(uint16_t)final_pid_reference[0]);
			i2cdev.writeWord(4 , (uint8_t)30 ,(uint16_t)final_pid_reference[1]);
		}
		else if(i == 2){
			i2cdev.writeWord(4 , (uint8_t)31 ,(uint16_t)final_pid_reference[0]);
			i2cdev.writeWord(4 , (uint8_t)32 ,(uint16_t)final_pid_reference[1]);
		}
		
	}

	//write depth pid values
	for( int i = 0 ; i < 3 ; i++ ){
		//takes first part of the number IE: 123.456 turns into 123
		final_pid_reference[0] = depth_pid[i] - (fmod(depth_pid[i], 1));

		//takes second part of number IE: 123.456 turns into 456
		final_pid_reference[1] = fmod(depth_pid[i], 1) * 1000;

		//write both parts of the number to the i2c bus on different registers

		if(i == 0){
			i2cdev.writeWord(4 , (uint8_t)33 ,(uint16_t)final_pid_reference[0]);
			i2cdev.writeWord(4 , (uint8_t)34 ,(uint16_t)final_pid_reference[1]);
		}
		else if(i == 1){
			i2cdev.writeWord(4 , (uint8_t)35 ,(uint16_t)final_pid_reference[0]);
			i2cdev.writeWord(4 , (uint8_t)36 ,(uint16_t)final_pid_reference[1]);
		}
		else if(i == 2){
			i2cdev.writeWord(4 , (uint8_t)37 ,(uint16_t)final_pid_reference[0]);
			i2cdev.writeWord(4 , (uint8_t)38 ,(uint16_t)final_pid_reference[1]);
		}
		
	}

	

}










