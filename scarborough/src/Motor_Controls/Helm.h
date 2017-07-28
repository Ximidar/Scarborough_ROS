#ifndef HELM_H
#define HELM_H
#include <control_toolbox/pid.h> 
//#include <angles/angles.h>
#include <iostream>
#include "scarborough/Motor_Speed.h"
#include "scarborough/Kill_Switch.h"
#include "scarborough/Desired_Directions.h"
#include "scarborough/YPR.h"
#include "scarborough/Depth.h"
#include "../HandlerNames/HANDLER_NAMES.h"
#include "ros/ros.h"
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <boost/algorithm/clamp.hpp>

using namespace std;

class Helm{

public:

	

	//PID updates
	control_toolbox::Pid yaw_pid;
	control_toolbox::Pid pitch_pid;
	control_toolbox::Pid roll_pid;
	control_toolbox::Pid depth_pid;

	Helm();
	void init();
	void update_helm();
	void update_desired(scarborough::Desired_Directions _desired);
	void update_YPR(scarborough::YPR _YPR);
	void update_depth(scarborough::Depth _depth);
	void computron();
	void reset();
	void load_yaml();
	double scale_output(double min_a, double max_a, double min_b, double max_b, double input);

	//variables for pid init
	double p;
    double i ;
    double d ;
    double imax ;
    double imin ;

	double YAW_CONST, PITCH_CONST, ROLL_CONST, DEPTH_CONST;
	double pid[3];
	double yaw_out, pitch_out, roll_out, depth_out;



	scarborough::Desired_Directions desired_input;
	scarborough::YPR ypr_input;
	scarborough::Depth depth_input;
	scarborough::Motor_Speed motor_output;
	
	ros::Time last_time;

};



#endif