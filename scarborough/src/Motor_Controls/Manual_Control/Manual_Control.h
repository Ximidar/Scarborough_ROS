#ifndef MANUAL_CONTROL_H
#define MANUAL_CONTROL_H

#include <iostream>
#include "ros/ros.h"
#include "scarborough/Desired_Directions.h"
#include "scarborough/YPR.h"
#include "scarborough/Kill_Switch.h"
#include "scarborough/Depth.h"
#include "scarborough/Vision_objects.h"
#include "../../HandlerNames/HANDLER_NAMES.h"
#include "scarborough/Hal.h"
#include <termios.h>
#include <stdio.h>
#include <unistd.h>

using namespace scarborough;
using namespace std;

class Manual_Control
{
public:
    Manual_Control();
    void change_speed(Desired_Directions direction);   
    int getch();

    Desired_Directions desired_motor_speed;
    ros::Publisher pub;
    ros::NodeHandle n;
};

#endif

