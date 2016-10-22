#include "accelerometer.h"

Handler handler;
scarborough::YPR _ypr;

void getdata(const scarborough::YPR& msg){

    _ypr = msg;
    cout<< "got Data" << endl;
   

}




int main(int argc, char **argv){

    ros::init(argc, argv, "accel");

    ros::NodeHandle n;
    ros::Subscriber imu;
    imu = n.subscribe(handler.IMU, 200, getdata);
    Accelerometer accel;

    while(ros::ok()){
        
         accel.accel_init(_ypr);

         ros::spinOnce();

    }


    
    
    return 0;
}