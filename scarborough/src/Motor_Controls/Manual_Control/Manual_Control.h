#ifndef MANUAL_CONTROL_H
#define MANUAL_CONTROL_H

#include <iostream>
#include "ros/ros.h"
#include "scarborough/Motor_Speed.h"
#include "../../HandlerNames/HANDLER_NAMES.h"
#include "../I2Cdev.h"
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
    void change_speed(Motor_Speed input);   
    int getch();

    Motor_Speed motor_speed;
    
private:
    I2Cdev i2cdev;
};

#endif

