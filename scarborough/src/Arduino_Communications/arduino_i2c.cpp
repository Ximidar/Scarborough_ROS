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

double imu_data[3];

/*
 * This function takes the data from the IMU_DATA publisher and throws it into a double that we can use.
 */
void getdata(const scarborough::YPR& msg){
	for(int i=0;i<2;i++){
		//cout << "casting to double" << endl;
		imu_data[i] = boost::lexical_cast<double>(msg.YPR[i]);

	}

}

//Main function for ArdI2C executable
int main(int argc, char **argv){

	ros::init(argc, argv, "ARD_I2C");
	ros::NodeHandle IMU;
	ros::NodeHandle n;

	ros::Subscriber imu;
	ros::Publisher ard_pub = n.advertise<scarborough::Motor_Speed>("ARD_I2C", 1000);

	i2c.init(); // does nothing.


	while(ros::ok()){

		//get IMU data
		imu = IMU.subscribe("IMU_DATA", 200, getdata);

		//write imu data to the arduino
		i2c.ardWrite(imu_data);

		//read message from arduino and parse it
		ardcomm.interperet_message(i2c.ardRead());

		//publish motor data to the ARD_I2C
		ard_pub.publish(ardcomm.motor);

		//spin once to let ROS you are alive.
		ros::spinOnce();
	}



}


ArdI2C::ArdI2C(){
	orientation = 0;
	sign = 0;
	delim = 255;
	arduino_message = "";
	 m1s = "";
	 m2s = "";
	 m3s = "";
	 m4s = "";
	 m5s = "";
	 m6s = "";

}
//use this if ever needed... It used to do something but is now a ghost of algorithms past
void ArdI2C::init(){



}

/*
 * ardWrite will take the IMU data and send it to the arduino for processing over the i2c bus.
 * Different registers will mean different things for example if we send a number to register 0 then the
 * first half of the number will be complete, but we also need to send a number to register 1 to complete
 * the number. IE:
 * 	sent to reg 0: -45
 * 	sent to reg 1: 576
 * 	final number on arduino side: -45.576
 *
 * 	only after the second register has been addressed will the number be completed and be usable.
 *
 * 	y = reg 0,1
 * 	p = reg 2,3
 * 	r = reg 4,5
 *
 */
void ArdI2C::ardWrite(double imu_data[3]){

	for(int i = 0; i < 2 ; i++){
		//takes first part of the number IE: 123.456 turns into 123
		final_reference[0] = imu_data[i] - (fmod(imu_data[i], 1));

		//takes second part of number IE: 123.456 turns into 456
		final_reference[1] = fmod(imu_data[i], 1) * 1000;

		//write both parts of the number to the i2c bus on different registers
		i2cdev.writeWord(4 , (uint8_t)(i*2) ,(uint16_t)final_reference[0]);
		i2cdev.writeWord(4 , (uint8_t)(i*2+1) ,(uint16_t)final_reference[1]);


	}
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

	//read all registeries from the arduino
	i2cdev.readBytes(4, 51, 30, m1);
	i2cdev.readBytes(4, 52, 30, m2);
	i2cdev.readBytes(4, 53, 30, m3);
	i2cdev.readBytes(4, 54, 30, m4);
	i2cdev.readBytes(4, 55, 30, m5);
	i2cdev.readBytes(4, 56, 30, m6);

	//make all variable strings be nothing.
	arduino_message = "";
	 m1s = "";
	 m2s = "";
	 m3s = "";
	 m4s = "";
	 m5s = "";
	 m6s = "";

	//load all strings with variables from the arduino read.
	for(int j = 0; j<128;j++){
		if(m1[j] != delim){
			m1s += m1[j];
		}
		if(m2[j] != delim){
			m2s += m2[j];
		}
		if(m3[j] != delim){
			m3s += m3[j];
		}
		if(m4[j] != delim){
			m4s += m4[j];
		}
		if(m5[j] != delim){
			m5s += m5[j];
		}
		if(m6[j] != delim){
			m6s += m6[j];
		}
	}

	//load all individual strings into one big string
	arduino_message = m1s + m2s + m3s + m4s + m5s + m6s;

	return arduino_message;
}










