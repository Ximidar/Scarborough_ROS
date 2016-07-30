#include "Helm.h"

Helm::Helm(){
	YAW_CONST = 0.5;
	PITCH_CONST = 0.5;
	ROLL_CONST = 0.5;
	DEPTH_CONST = 0.5;

	double pid[3] = {
		0.2,
		0.0,
		0.0
	};
	yaw_pid.initPid(pid[0], pid[1], pid[2], 1100, 1900);
	pitch_pid.initPid(pid[0], pid[1], pid[2], 1100, 1900);
	roll_pid.initPid(pid[0], pid[1], pid[2], 1100, -1900);
	depth_pid.initPid(pid[0], pid[1], pid[2], 1100, 1900);

}

void Helm::init(){
	//init something here maybe
	last_time = ros::Time::now();
}

void Helm::update_helm(){
	ros::Time time = ros::Time::now();
	
	yaw_out = yaw_pid.updatePid(ypr_input.YPR[0] - desired_input.rotation[0], time - last_time);
	pitch_out = pitch_pid.updatePid(ypr_input.YPR[1] - desired_input.rotation[1], time - last_time);
	roll_out = roll_pid.updatePid(ypr_input.YPR[2] - desired_input.rotation[2], time - last_time);
	depth_out = depth_pid.updatePid(depth_input.depth - desired_input.depth, time - last_time);
	last_time = ros::Time::now();	
}

void Helm::computron(){
	motor_output.motor[0] = (-YAW_CONST * yaw_out) + (PITCH_CONST * pitch_out) + desired_input.throttle;
    motor_output.motor[1] = (YAW_CONST * yaw_out) + (PITCH_CONST * pitch_out) + desired_input.throttle;

    //dive motors
    motor_output.motor[2] = (PITCH_CONST * pitch_out) + (ROLL_CONST * roll_out) + (DEPTH_CONST * depth_out);
    motor_output.motor[3] = (PITCH_CONST * pitch_out) + (-ROLL_CONST * roll_out) + (DEPTH_CONST * depth_out);
    motor_output.motor[4] = (-PITCH_CONST * pitch_out) + (-ROLL_CONST * roll_out) + (DEPTH_CONST * depth_out);
    motor_output.motor[5] = (-PITCH_CONST * pitch_out) + (ROLL_CONST * roll_out) + (DEPTH_CONST * depth_out);


    //clamp the values
    for(int i = 0 ; i < 6 ; i++){
    	if(motor_output.motor[i] > 1900){
    		motor_output.motor[i] = 1900;
    	}
    	if(motor_output.motor[i] < 1100){
    		motor_output.motor[i] = 1100;
    	}
    }
}

void Helm::reset(){
	yaw_pid.reset();
	pitch_pid.reset();
	roll_pid.reset();
	depth_pid.reset();
}

void Helm::update_desired(scarborough::Desired_Directions _desired){
	desired_input = _desired;
}

void Helm::update_YPR(scarborough::YPR _YPR){
	ypr_input = _YPR;
}

void Helm::update_depth(scarborough::Depth _depth){
	depth_input = _depth;
}