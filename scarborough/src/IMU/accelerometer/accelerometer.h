#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "ros/ros.h"
#include <iostream>
#include "scarborough/YPR.h"
#include <boost/lexical_cast.hpp> //used to cast from number to string
#include "../../HandlerNames/HANDLER_NAMES.h"


using namespace std;

class Accelerometer{
public:
    Accelerometer();
    ~Accelerometer();

    void accel_init(scarborough::YPR YPR);
    
};

#endif