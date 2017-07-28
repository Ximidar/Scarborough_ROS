#ifndef IMU2_H
#define IMU2_H

#include "RTIMULib.h"
#include "scarborough/YPR.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <iostream>

using namespace std;


class IMU2{

public:
	IMU2() ;
	
	void get_imu() ;
	void init_imu()	;
	bool Ok() ;
	uint64_t rateTimer;
    uint64_t displayTimer;
    uint64_t now;
    
	scarborough::YPR ypr_ROS;
private:
	RTIMUSettings *settings;

    RTIMU *imu;
	
	    
	    

};

#endif