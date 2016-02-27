/*
 * IMU.cpp
 *
 *  Created on: Feb 12, 2016
 *      Author: ubuntu
 */
#define NO_I2C
//#define NORMAL_OP

#include "IMU.h"
//TODO create a debug function that will override addressing the i2c bus since some computers don't have a usable one.
//declare imu object
IMU imu;

//TODO this main needs to have a ROS publisher attached to it.
int main(int argc, char **argv) {
	ros::init(argc, argv, "arduino_chatter");

	ros::NodeHandle n;

	ros::Publisher ard_pub = n.advertise<scarborough::YPR>("IMU_DATA", 200);
#ifdef NORMAL_OP
    imu.IMU_init();

    while(ros::ok()){
    	imu.read_IMU();

    	ard_pub.publish(imu.ypr_ROS.YPR);

    	ros::spinOnce();
    	//loop_rate.sleep();
    }
#endif
//if there's no I2C on the computer then use this to spit out some numbers.
#ifdef NO_I2C

    //set up a loop rate since we are sending debug data
    ros::Rate loop_rate(100);
    //initialize debug_d to 0;
    imu.debug_d = 0;
    //while ros isn't shut down send out all the data
    while(ros::ok()){
    	//Dont call up any of imu's actual functions. This is for testing at home.
    	imu.debug_d++;
    	//fill the publisher with the debug data
    	imu.ypr_ROS.YPR = {imu.debug_d, imu.debug_d, imu.debug_d};
    	//publish the debug data
    	ard_pub.publish(imu.ypr_ROS.YPR);
    	ros::spinOnce();
    	loop_rate.sleep();
    }
#endif


}


IMU::IMU(){
	dmpReady = false;

}

void IMU::IMU_init(){
	 // initialize device
	    printf("Initializing I2C devices...\n");
	    mpu.initialize();

	    // verify connection
	    printf("Testing device connections...\n");
	    //wait until we get a connection.
	   	while(mpu.testConnection() == false ){
	   		cout << ".";
	   	}
	    printf(mpu.testConnection() ? "MPU6050 connection successful\n" : "MPU6050 connection failed\n");


	    // load and configure the DMP
	    printf("Initializing DMP...\n");
	    devStatus = mpu.dmpInitialize();

	    // make sure it worked (returns 0 if so)
	    if (devStatus == 0) {
	        // turn on the DMP, now that it's ready
	        printf("Enabling DMP...\n");
	        mpu.setDMPEnabled(true);

	        // enable Arduino interrupt detection
	        //Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
	        //attachInterrupt(0, dmpDataReady, RISING);
	        mpuIntStatus = mpu.getIntStatus();

	        // set our DMP Ready flag so the main loop() function knows it's okay to use it
	        printf("DMP ready!\n");
	        dmpReady = true;

	        // get expected DMP packet size for later comparison
	        packetSize = mpu.dmpGetFIFOPacketSize();
	    } else {
	        // ERROR!
	        // 1 = initial memory load failed
	        // 2 = DMP configuration updates failed
	        // (if it's going to break, usually the code will be 1)
	        printf("DMP Initialization failed (code %d)\n", devStatus);
	    }
}

//TODO read_IMU needs to have an array passed into it to have the array populated with the YPR angles.
//TODO read_IMU needs to be split into different functions that return the different types of data instead of having things be defined. It just looks nicer.
void IMU::read_IMU(){
	// if programming failed, don't try to do anything
	    if (!dmpReady) return;
	    // get current FIFO count
	    fifoCount = mpu.getFIFOCount();

	    if (fifoCount == 1024) {
	        // reset so we can continue cleanly
	        mpu.resetFIFO();
	        printf("FIFO overflow!\n");

	    // otherwise, check for DMP data ready interrupt (this should happen frequently)
	    } else if (fifoCount >= 42) {
	        // read a packet from FIFO
	        mpu.getFIFOBytes(fifoBuffer, packetSize);

	        #ifdef OUTPUT_READABLE_QUATERNION
	            // display quaternion values in easy matrix form: w x y z
	            mpu.dmpGetQuaternion(&q, fifoBuffer);
	            printf("quat %7.2f %7.2f %7.2f %7.2f    ", q.w,q.x,q.y,q.z);
	        #endif

	        #ifdef OUTPUT_READABLE_EULER
	            // display Euler angles in degrees
	            mpu.dmpGetQuaternion(&q, fifoBuffer);
	            mpu.dmpGetEuler(euler, &q);
	            printf("euler %7.2f %7.2f %7.2f    ", euler[0] * 180/M_PI, euler[1] * 180/M_PI, euler[2] * 180/M_PI);
	        #endif

	        #ifdef OUTPUT_READABLE_YAWPITCHROLL
	            // display Euler angles in degrees
	            mpu.dmpGetQuaternion(&q, fifoBuffer);
	            mpu.dmpGetGravity(&gravity, &q);
	            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
	            //printf("ypr  %7.2f %7.2f %7.2f    ", ypr[0] * 180/M_PI, ypr[1] * 180/M_PI, ypr[2] * 180/M_PI);
	            imu.ypr_ROS.YPR[0] =  ypr[0] * 180/M_PI;
	            imu.ypr_ROS.YPR[1] =  ypr[1] * 180/M_PI;
	            imu.ypr_ROS.YPR[2] =  ypr[2] * 180/M_PI;
	            cout << "YPR: " << imu.ypr_ROS.YPR[0]
	                            << " "
	                            << imu.ypr_ROS.YPR[1]
							    << " "
							    << imu.ypr_ROS.YPR[2] << endl;
	        #endif

	        #ifdef OUTPUT_READABLE_REALACCEL
	            // display real acceleration, adjusted to remove gravity
	            mpu.dmpGetQuaternion(&q, fifoBuffer);
	            mpu.dmpGetAccel(&aa, fifoBuffer);
	            mpu.dmpGetGravity(&gravity, &q);
	            mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
	            printf("areal %6d %6d %6d    ", aaReal.x, aaReal.y, aaReal.z);
	        #endif

	        #ifdef OUTPUT_READABLE_WORLDACCEL
	            // display initial world-frame acceleration, adjusted to remove gravity
	            // and rotated based on known orientation from quaternion
	            mpu.dmpGetQuaternion(&q, fifoBuffer);
	            mpu.dmpGetAccel(&aa, fifoBuffer);
	            mpu.dmpGetGravity(&gravity, &q);
	            mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
	            printf("aworld %6d %6d %6d    ", aaWorld.x, aaWorld.y, aaWorld.z);
	        #endif


	        printf("\n");
	    }
}


