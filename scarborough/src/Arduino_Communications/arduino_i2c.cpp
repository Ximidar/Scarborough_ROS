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
	ros::Publisher ard_pub = n.advertise<scarborough::Motor_Speed>("ARD_I2C", 200);

	i2c.init(); // does nothing.


	while(ros::ok()){

		//get IMU data
		imu = IMU.subscribe("IMU_DATA", 200, getdata);

		//write imu data to the arduino
		i2c.ardWrite(imu_data);

		//read message from arduino and parse it
		ardcomm.interperet_message(i2c.ardRead());
		//cout << i2c.ardRead() << endl;

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
	 desired_yaw = 0;
	 desired_depth = 4;

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
	for(int j = 0; j<30;j++){
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

	//output to console for debug purposes.
	cout << arduino_message << endl;
	return arduino_message;
}


/*
 * This function will update the desired yaw(reg 9) and desired depth (reg 10)
 * Then write it to the arduino.
 */
void ArdI2C::update_desired(int type, int value){

	switch(type){

		case YAW:
			i2cdev.writeWord(4, 9, (uint16_t)value);
			desired_yaw = value;
			break;

		case DEPTH:
			i2cdev.writeWord(4, 10, (uint16_t)value);
			desired_depth = value;
			break;
	}

}

/*
 * This function writes to the i2c bus the values for kp, ki, and kd. The number it writes
 * will be divided by 100 on the arduino side so 100 would turn into 1, while 25 would turn into 0.25.
 * This is because we cannot send doubles and its such a small number that it works well this way.
 *
 * TODO Matt Pedler: In the future we need to expand this to be able to switch any motors PID value
 * TODO Matt Pedler: check the registers on this to make sure they are the correct ones
 */

void ArdI2C::pid_Control(int motor, int mode){

	//Set up bool for switching
	bool switcher = false;

	int kp_addr;
	int ki_addr;
	int kd_addr;

	//detirmine motor addresses TODO Matt Pedler
	while(switcher != true){
			switch(motor){
			case 1:
				kp_addr = 6;
				ki_addr = 7;
				kd_addr = 8;
				switcher = false;
				break;

			case 2:
				kp_addr = 6;
				ki_addr = 7;
				kd_addr = 8;
				switcher = false;
				break;

			case 3:
				kp_addr = 6;
				ki_addr = 7;
				kd_addr = 8;
				switcher = false;
				break;

			case 4:
				kp_addr = 6;
				ki_addr = 7;
				kd_addr = 8;
				switcher = false;
				break;

			case 5:
				kp_addr = 6;
				ki_addr = 7;
				kd_addr = 8;
				switcher = false;
				break;

			case 6:
				kp_addr = 6;
				ki_addr = 7;
				kd_addr = 8;
				switcher = false;
				break;
			}
		}
	switcher = false;

	//set up while loop for switching
	while(switcher != true){
		switch(mode){
		case AGRESSIVE:
			i2cdev.writeWord(4, (uint8_t)kp_addr, 100);
			i2cdev.writeWord(4, (uint8_t)ki_addr, 100);
			i2cdev.writeWord(4, (uint8_t)kd_addr, 100);
			switcher = true;
			break;
		case MEDIUM:
			i2cdev.writeWord(4, (uint8_t)kp_addr, 100);
			i2cdev.writeWord(4, (uint8_t)ki_addr, 25);
			i2cdev.writeWord(4, (uint8_t)kd_addr, 5);
			switcher = true;
			break;

		case FINE:
			i2cdev.writeWord(4, (uint8_t)kp_addr, 100);
			i2cdev.writeWord(4, (uint8_t)ki_addr, 5);
			i2cdev.writeWord(4, (uint8_t)kd_addr, 1);
			switcher = true;
			break;
		}
	}

}

/*
 * This function monitors desired values vs reference values and changes the PID state accordingly
 */

void ArdI2C::pid_monitor(){

	double disparity = fabs(imu_data[0] - desired_yaw);

	if(disparity > 10){

		pid_Control(1, AGRESSIVE);
		pid_Control(2, AGRESSIVE);

	}
	else if(disparity <= 9 && disparity > 5){
		pid_Control(1, MEDIUM);
		pid_Control(2, MEDIUM);
	}
	else if(disparity <= 5){
		pid_Control(1, FINE);
		pid_Control(2, FINE);
	}

}









