#ifndef HELM_H
#define HELM_H
#include <control_toolbox/pid.h> 
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

	//returns the smallest absolute value angle equivalent to the given angle
	static double normalizeAngle(const double& angle); //degrees

	double YAW_CONST, PITCH_CONST, ROLL_CONST, DEPTH_CONST;

	scarborough::Desired_Directions desired_input;
	scarborough::YPR ypr_input;
	scarborough::Depth depth_input;
	scarborough::Motor_Speed motor_output;
	double yaw_out, pitch_out, roll_out, depth_out;
	ros::Time last_time;

};



#endif