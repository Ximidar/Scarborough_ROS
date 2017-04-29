#include "Helm.h"

Helm::Helm(){
    //here are the constants for making a signal stronger or weaker. 
	YAW_CONST = 1;
	PITCH_CONST = 1;
	ROLL_CONST = 1;
	DEPTH_CONST = 1;

    //this will initialize the PID value
	load_yaml();
    //this gives the PID the P, I and D values then limits their output with a min and a max
	yaw_pid.initPid(pid[0], pid[1], pid[2], 1200, 1800);
	pitch_pid.initPid(pid[0], pid[1], pid[2], 1200, 1800);
	roll_pid.initPid(pid[0], pid[1], pid[2], 1200, 1800);
	depth_pid.initPid(pid[0], pid[1], pid[2], 1200, 1800);

}

void Helm::init(){
	//initialize the time
	last_time = ros::Time::now();   


}

void Helm::load_yaml(){
    ifstream config("/home/ros/PID_config.txt");

    double P = 0.00;
    double I = 0.00;
    double D = 0.00;


    for( string line; getline( config, line ); )
    {
        cout << line << endl;
        switch(line[0]){

            case 'P':
                P = atof( line.substr(1, line.length()).c_str() );
                break;
            case 'I':
                I = atof( line.substr(1, line.length()).c_str() );
                break;
            case 'D':
                D = atof( line.substr(1, line.length()).c_str() );
                break;
            default:
                break;


        }
    }

    cout << "P: " << P << endl;
    cout << "I: " << I << endl;
    cout << "D: " << D << endl;

    pid[0] = P;
    pid[1] = I;
    pid[2] = D;

}


//
void Helm::update_helm(){
    //grab the time
	ros::Time time = ros::Time::now();
	
    //calculate error
	double yaw_error = ypr_input.YPR[0] - desired_input.rotation[0];
	double pitch_error = ypr_input.YPR[1] - desired_input.rotation[1];
	double roll_error = ypr_input.YPR[2] - desired_input.rotation[2];
    double depth_error = depth_input.depth - desired_input.depth;

    //measuring error over time
	yaw_out = yaw_pid.updatePid(yaw_error, time - last_time);
	pitch_out = pitch_pid.updatePid(pitch_error, time - last_time);
	roll_out = roll_pid.updatePid(roll_error, time - last_time);
	depth_out = depth_pid.updatePid(depth_error, time - last_time);

    //grab time again
	last_time = ros::Time::now();	
}

void Helm::computron(){

    if(desired_input.mode == "DIVE"){

        motor_output.motor[0] = 1500;
        motor_output.motor[1] = 1500;
        //calculate dive motors
        motor_output.motor[2] = (PITCH_CONST * pitch_out) + (ROLL_CONST * roll_out) + (-DEPTH_CONST * depth_out);
        motor_output.motor[3] = (PITCH_CONST * pitch_out) + (-ROLL_CONST * roll_out) + (-DEPTH_CONST * depth_out);
        motor_output.motor[4] = (-PITCH_CONST * pitch_out) + (-ROLL_CONST * roll_out) + (-DEPTH_CONST * depth_out);
        motor_output.motor[5] = (-PITCH_CONST * pitch_out) + (ROLL_CONST * roll_out) + (-DEPTH_CONST * depth_out );

    }
    else if(desired_input.mode == "NORMAL_OP"){
        //calculate forward motors
        motor_output.motor[0] = (-YAW_CONST * yaw_out) + (PITCH_CONST * pitch_out) + desired_input.throttle;
        motor_output.motor[1] = (YAW_CONST * yaw_out) + (PITCH_CONST * pitch_out) + desired_input.throttle;
    
        //calculate dive motors
        motor_output.motor[2] = (PITCH_CONST * pitch_out) + (ROLL_CONST * roll_out) + (-DEPTH_CONST * depth_out);
        motor_output.motor[3] = (PITCH_CONST * pitch_out) + (-ROLL_CONST * roll_out) + (-DEPTH_CONST * depth_out);
        motor_output.motor[4] = (-PITCH_CONST * pitch_out) + (-ROLL_CONST * roll_out) + (-DEPTH_CONST * depth_out);
        motor_output.motor[5] = (-PITCH_CONST * pitch_out) + (ROLL_CONST * roll_out) + (-DEPTH_CONST * depth_out );
    }
    else{
        motor_output.motor[0] = 1500; 
        motor_output.motor[1] = 1500;
        //calculate dive motors
        motor_output.motor[2] = 1500;
        motor_output.motor[3] = 1500;
        motor_output.motor[4] = 1500;
        motor_output.motor[5] = 1500;
    }

    


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

//reset the PID
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
