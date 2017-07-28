
#include "Dead_Motors.h"

Dead_Motors::Dead_Motors(){

    for (int i =2 ; i < 6; i++){
        motor_output.motor[i] = 1500;
    }

    motor_output.motor[0] = 1500;
    motor_output.motor[1] = 1500;
    
}
Dead_Motors::~Dead_Motors(){
    
}

int Dead_Motors::adjust_motor(bool dive, int motor, int adjustment_amount,double max_offset, double orientation, double desired_orientation){

    int motor_out = motor;

    if ( desired_orientation > orientation + max_offset){
        motor_out += adjustment_amount ;
    }
    else if ( desired_orientation  < orientation - max_offset ){
        motor_out -= adjustment_amount ;

    }
    cout << (desired_orientation > orientation + max_offset) << endl;
    cout << (desired_orientation  < orientation - max_offset) << endl;
    if(dive){
        return clamp_dive(motor_out);
    }
    return clamp(motor_out);
    
}

int Dead_Motors::clamp_dive(int value){
    if (value > 1550){
        value = 1550;
    }
    if (value < 1300){
        value = 1300;
    }
    return value;
}
int Dead_Motors::clamp(int value){
    if (value > 1650){
        value = 1650;
    }
    if (value < 1200){
        value = 1200;
    }
    return value;
}

void Dead_Motors::dive(scarborough::Depth cur_depth, scarborough::YPR cur_orientation, scarborough::Desired_Directions des_orientation){

    //do not engage the forward motors
    motor_output.motor[0] = 1500;
    motor_output.motor[1] = 1500;

    //set dive strength
    motor_output.motor[2] = adjust_motor(true, motor_output.motor[2], -5, 0.1, (double)cur_depth.depth, (double)des_orientation.depth);
    motor_output.motor[3] = adjust_motor(true, motor_output.motor[3], -5, 0.1, (double)cur_depth.depth, (double)des_orientation.depth);
    motor_output.motor[4] = adjust_motor(true, motor_output.motor[4], -5, 0.1, (double)cur_depth.depth, (double)des_orientation.depth);
    motor_output.motor[5] = adjust_motor(true, motor_output.motor[5], -5, 0.1, (double)cur_depth.depth, (double)des_orientation.depth);
    

    //adjust for roll
    //left
    // motor_output.motor[2] = adjust_motor(motor_output.motor[2], -10,  (double)cur_orientation.YPR[2], (double)des_orientation.rotation[2]);
    // motor_output.motor[5] = adjust_motor(motor_output.motor[5], -10,  (double)cur_orientation.YPR[2], (double)des_orientation.rotation[2]);
    // //right
    // motor_output.motor[3] = adjust_motor(motor_output.motor[3], 10,  (double)cur_orientation.YPR[2], (double)des_orientation.rotation[2]);
    // motor_output.motor[4] = adjust_motor(motor_output.motor[4], 10,  (double)cur_orientation.YPR[2], (double)des_orientation.rotation[2]);


    // //adjust for pitch
    // //front
    // motor_output.motor[2] = adjust_motor(motor_output.motor[2], 10,  (double)cur_orientation.YPR[2], (double)des_orientation.rotation[2]);
    // motor_output.motor[4] = adjust_motor(motor_output.motor[4], 10,  (double)cur_orientation.YPR[2], (double)des_orientation.rotation[2]);

    // //back
    // motor_output.motor[4] = adjust_motor(motor_output.motor[4], -10,  (double)cur_orientation.YPR[3], (double)des_orientation.rotation[3]);
    // motor_output.motor[5] = adjust_motor(motor_output.motor[5], -10,  (double)cur_orientation.YPR[3], (double)des_orientation.rotation[3]);
}


void Dead_Motors::keep_heading(scarborough::Depth cur_depth, scarborough::YPR cur_orientation, scarborough::Desired_Directions des_orientation){
    //do not engage the forward motors
    //motor_output.motor[0] = adjust_motor(false, motor_output.motor[0], -1, 10, (double)cur_orientation.YPR[0], (double)des_orientation.rotation[0]);
    //motor_output.motor[1] = adjust_motor(false, motor_output.motor[1], 1, 10, (double)cur_orientation.YPR[0], (double)des_orientation.rotation[0]);
    motor_output.motor[0] = 1700;
    motor_output.motor[1] = 1700;
    //set dive strength
    motor_output.motor[2] = adjust_motor(false, motor_output.motor[2], -5, 0.1, (double)cur_depth.depth, (double)des_orientation.depth);
    motor_output.motor[3] = adjust_motor(false, motor_output.motor[3], -5, 0.1, (double)cur_depth.depth, (double)des_orientation.depth);
    motor_output.motor[4] = adjust_motor(false, motor_output.motor[4], -5, 0.1, (double)cur_depth.depth, (double)des_orientation.depth);
    motor_output.motor[5] = adjust_motor(false, motor_output.motor[5], -5, 0.1, (double)cur_depth.depth, (double)des_orientation.depth);
    
}