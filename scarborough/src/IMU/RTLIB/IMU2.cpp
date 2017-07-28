#include "IMU2.h"

IMU2::IMU2(){
	settings = new RTIMUSettings("/home/ubuntu/","RTIMULib");

    imu = RTIMU::createIMU(settings);
    rateTimer = displayTimer = RTMath::currentUSecsSinceEpoch();
    init_imu();   

   
}

void IMU2::init_imu(){
	if ((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL)) {
        cout << "No IMU found" << endl;
        exit(1);
    }
	 //  This is an opportunity to manually override any settings before the call IMUInit

    //  set up IMU

    imu->IMUInit();
    imu->setSlerpPower(0.02);
    imu->setGyroEnable(true);
    imu->setAccelEnable(true);
    imu->setCompassEnable(false);


}

void IMU2::get_imu(){
	usleep(imu->IMUGetPollInterval() * 1000);

	now = RTMath::currentUSecsSinceEpoch();

	RTIMU_DATA imuData = imu->getIMUData();

	ypr_ROS.YPR[1] = (float)imuData.fusionPose.x() * RTMATH_RAD_TO_DEGREE;
    ypr_ROS.YPR[2] = (float)imuData.fusionPose.y() * RTMATH_RAD_TO_DEGREE;
    ypr_ROS.YPR[0] = (float)imuData.fusionPose.z() * RTMATH_RAD_TO_DEGREE;

    if ((now - displayTimer) > 100000) {

    	cout << RTMath::displayDegrees("", imuData.fusionPose) << endl;
    	displayTimer = now;
    }
}

bool IMU2::Ok(){ return imu->IMURead() ;}