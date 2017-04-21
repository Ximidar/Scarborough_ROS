/*
 * IMU.cpp
 *
 *  Created on: Feb 12, 2016
 *      Author: ubuntu
 */
//#define NO_I2C


#include "IMU.h"

//TODO create a debug function that will override addressing the i2c bus since some computers don't have a usable one.
//declare imu object
IMU imu;
bool killer;
bool getkiller = false;

void getdata_KILL(const scarborough::Kill_Switch& msg){
	cout << msg << " GETDATA" << endl;
	killer = msg.killed;
	getkiller = true;

}


Handler handler;
int main(int argc, char **argv) {
	cout << "initializing ROS" << endl;
	ros::init(argc, argv, handler.IMU_CHATTER);

	ros::NodeHandle n;
	ros::NodeHandle kill;
	ros::Subscriber sub;



	ros::Publisher imu_pub = n.advertise<scarborough::YPR>(handler.IMU, 200);
        sub = kill.subscribe(handler.KILL, 20, getdata_KILL);


	
    //cout << "Initializing IMU" << endl;
    imu.IMU_init();
    //imu.set_zero(); // many offsets have calculated this number as YPR_OFFSET: -13.1352 -0.686341 -0.702521
    bool restart = true;
    killer = true;
    while(ros::ok()){

    		imu.read_IMU();

    		imu_pub.publish(imu.ypr_ROS.YPR);
			ros::spinOnce();

    }




}


IMU::IMU(){
	dmpReady = false;

	ypr_offset[0] = -13.1352;
	ypr_offset[1] = -0.686341;
	ypr_offset[2] = -0.702521;

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
	       // printf("FIFO overflow!\n");

	    // otherwise, check for DMP data ready interrupt (this should happen frequently)
	    } else if (fifoCount >= 42) {
	        // read a packet from FIFO
	        mpu.getFIFOBytes(fifoBuffer, packetSize);

	        OUTPUT_READABLE_YAWPITCHROLL
	            // display Euler angles in degrees
	            mpu.dmpGetQuaternion(&q, fifoBuffer);
	            mpu.dmpGetGravity(&gravity, &q);
	            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
	            //printf("ypr  %7.2f %7.2f %7.2f    ", ypr[0] * 180/M_PI, ypr[1] * 180/M_PI, ypr[2] * 180/M_PI);
	            imu.ypr_ROS.YPR[0] =  (ypr[0] * 180/M_PI) * -1;
	            imu.ypr_ROS.YPR[1] =  (ypr[2] * 180/M_PI) * -1;
	            imu.ypr_ROS.YPR[2] =  (ypr[1] * 180/M_PI) * -1;

	            //output current rotation
	            cout << "YPR: " << imu.ypr_ROS.YPR[0]
	                            << " "
	                            << imu.ypr_ROS.YPR[1]
							    << " "
							    << imu.ypr_ROS.YPR[2];
	        

	      


	        printf("\n");
	    }
}
/*
 * This function waits for the IMU to settle then sets the zero point for the entire class.
 *
 */

void IMU::set_zero(){
	cout << "Setting Zero\n";
	for(int i = 0; i < 50000; i++){
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

			// display Euler angles in degrees
			mpu.dmpGetQuaternion(&q, fifoBuffer);
			mpu.dmpGetGravity(&gravity, &q);
			mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
			//printf("ypr  %7.2f %7.2f %7.2f    ", ypr[0] * 180/M_PI, ypr[1] * 180/M_PI, ypr[2] * 180/M_PI);
			ypr_offset[0] =  ypr[0] * 180/M_PI;
			ypr_offset[1] =  ypr[1] * 180/M_PI;
			ypr_offset[2] =  ypr[2] * 180/M_PI;
			cout <<"\r" << i ;


		}
	}
	cout << "\nYPR_OFFSET: " <<  ypr_offset[0]
						   << " "
				           <<  ypr_offset[1]
						   << " "
						   <<  ypr_offset[2]
						   <<"\n";


}


