#include "Helm.h"

Helm::Helm(){
    //here are the constants for making a signal stronger or weaker. 
	YAW_CONST = 1.0;
	PITCH_CONST = 1.0;
	ROLL_CONST = 1.0;
	DEPTH_CONST = 1.0;

    //this will initialize the PID value
	load_yaml();
    //this gives the PID the P, I and D values then limits their output with a min and a max

    p = pid[0];
    i = pid[1];
    d = pid[2];
    imax = 0.00;
    imin = 2.00;
	yaw_pid.initPid(p, i, d, imin, imax);
	pitch_pid.initPid(p, i, d, imin, imax);
	roll_pid.initPid(p, i, d, imin, imax);
	depth_pid.initPid(p, i, d, imin, imax);

}

void Helm::init(){
	//initialize the time
	last_time = ros::Time::now();   


}

void Helm::load_yaml(){
    ifstream config("/home/ubuntu/PID_config.txt");

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
            case 'Y':
                YAW_CONST = atof( line.substr(1, line.length()).c_str() );
                break;
            case 'O':
                PITCH_CONST = atof( line.substr(1, line.length()).c_str() );
                break;
            case 'R':
                ROLL_CONST = atof( line.substr(1, line.length()).c_str() );
                break;
            case 'S':
                DEPTH_CONST = atof( line.substr(1, line.length()).c_str() );
                break;
            default:
                break;


        }
    }

    

    pid[0] = P;
    pid[1] = I;
    pid[2] = D;

    cout << "P: " << pid[0] << endl;
    cout << "I: " << pid[1] << endl;
    cout << "D: " << pid[2] << endl;
    cout << "YC" << YAW_CONST << endl;
    cout << "PC" << PITCH_CONST << endl;
    cout << "RC" << ROLL_CONST << endl; 
    cout << "DC" << DEPTH_CONST << endl;

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
	yaw_out = yaw_pid.computeCommand(yaw_error, time - last_time);
    yaw_out = yaw_pid.computeCommand(yaw_error, yaw_out, time - last_time);

	pitch_out = pitch_pid.computeCommand(pitch_error, time - last_time);
    pitch_out = pitch_pid.computeCommand(pitch_error, pitch_out, time - last_time);

	roll_out = roll_pid.computeCommand(roll_error, time - last_time);
    roll_out = roll_pid.computeCommand(roll_error, roll_out, time - last_time);

	depth_out = depth_pid.computeCommand(depth_error, time - last_time);
    depth_out = depth_pid.computeCommand(depth_error, depth_out, time - last_time);

    //grab time again
	last_time = ros::Time::now();	
}

void Helm::computron(){

    
    //calculate forward motors
    motor_output.motor[0] = (-YAW_CONST * yaw_out) + desired_input.throttle;
    motor_output.motor[1] = (YAW_CONST * yaw_out) + desired_input.throttle;

    //calculate dive motors
    motor_output.motor[2] = (-PITCH_CONST * pitch_out) + (-ROLL_CONST * roll_out) + (-DEPTH_CONST * depth_out);
    motor_output.motor[3] = (-PITCH_CONST * pitch_out) + (ROLL_CONST * roll_out) + (-DEPTH_CONST * depth_out);
    motor_output.motor[4] = (PITCH_CONST * pitch_out) + (ROLL_CONST * roll_out) + (-DEPTH_CONST * depth_out);
    motor_output.motor[5] = (PITCH_CONST * pitch_out) + (-ROLL_CONST * roll_out) + (-DEPTH_CONST * depth_out );
    
    //clamp the values
    for(int i = 0 ; i < 6 ; i++){

        //clamp motor output to 50000
        if( motor_output.motor[i] > 10000){
            motor_output.motor[i] = 10000;
        }
        else if (motor_output.motor[i] < -10000){
            motor_output.motor[i] = -10000;
        }

        if (motor_output.motor[i] > 0){
            motor_output.motor[i] = (int)scale_output(0, 10000.00, 1525.00, 1800.00, (double)motor_output.motor[i]);
        }
        else if (motor_output.motor[i] <= 0){
            motor_output.motor[i] = (int)scale_output(-10000.00, 0.00, 1200.00, 1475.00, (double)motor_output.motor[i]);
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

double Helm::scale_output(double istart, double istop, double ostart, double ostop, double value){
    
    double output = ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
    //cout << output << endl;
    return output;
}
