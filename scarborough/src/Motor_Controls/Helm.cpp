#include "Helm.h"

Helm::Helm(){
	YAW_CONST = 1;
	PITCH_CONST = 1;
	ROLL_CONST = 2;
	DEPTH_CONST = 4;
	double pid[3] = {
		65,
		0,
		0
	};
	yaw_pid.initPid(pid[0], pid[1], pid[2], 1200, 1800);
	pitch_pid.initPid(pid[0], pid[1], pid[2], 1200, 1800);
	roll_pid.initPid(pid[0], pid[1], pid[2], 1200, 1800);
	depth_pid.initPid(pid[0], pid[1], pid[2], 1200, 1800);

}

void Helm::init(){
	//init something here maybe
	last_time = ros::Time::now();
}

void Helm::update_helm(){
	ros::Time time = ros::Time::now();
	
	double yaw_error = ypr_input.YPR[0] - desired_input.rotation[0];
	double pitch_error = ypr_input.YPR[1] - desired_input.rotation[1];
	double roll_error = ypr_input.YPR[2] - desired_input.rotation[2];


	yaw_out = yaw_pid.updatePid(yaw_error, time - last_time);
	pitch_out = pitch_pid.updatePid(pitch_error, time - last_time);
	roll_out = roll_pid.updatePid(roll_error, time - last_time);
	depth_out = depth_pid.updatePid(depth_input.depth - desired_input.depth, time - last_time);
	last_time = ros::Time::now();	
}

void Helm::computron(){
	motor_output.motor[0] = (-YAW_CONST * yaw_out) + (PITCH_CONST * pitch_out) + desired_input.throttle;
    motor_output.motor[1] = (YAW_CONST * yaw_out) + (PITCH_CONST * pitch_out) + desired_input.throttle;

    //dive motors
    motor_output.motor[2] = (PITCH_CONST * pitch_out) + (ROLL_CONST * roll_out) + (-DEPTH_CONST * depth_out);
    motor_output.motor[3] = (PITCH_CONST * pitch_out) + (-ROLL_CONST * roll_out) + (-DEPTH_CONST * depth_out);
    motor_output.motor[4] = (-PITCH_CONST * pitch_out) + (-ROLL_CONST * roll_out) + (-DEPTH_CONST * depth_out);
    motor_output.motor[5] = (-PITCH_CONST * pitch_out) + (ROLL_CONST * roll_out) + (-DEPTH_CONST * depth_out );


    //clamp the values
    for(int i = 0 ; i < 6 ; i++){
    	if(motor_output.motor[i] > 1800){
    		motor_output.motor[i] = 1800;
    	}
    	if(motor_output.motor[i] < 1200){
    		motor_output.motor[i] = 1200;
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

double Helm::normalizeAngle(const double& angle)
{
	double result = angle;
	
	if (result > 180)
		result -= 360;
	
	if (result < -180)
		result += 360;
	
	return result;
}
