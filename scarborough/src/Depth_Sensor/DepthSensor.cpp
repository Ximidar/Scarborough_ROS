/*
 * DepthSensor.cpp
 *
 *  Created on: May 31, 2016
 *      Author: ximidar
 */
#include "anchor.h"
#include "scarborough/Depth.h"

Anchor depthSensor;
scarborough::Depth realDepth;

void start(){
	depthSensor.init();

	//set fluid density. 997 for freshwater 1029 for saltwater
	depthSensor.setFluidDensity(997);

}

int main(int argc, char **argv){

	//initialize the depth sensor
	start();

	//initialize ros
	ros::init(argc, argv, "DEPTH");
	ros::NodeHandle depth;

	ros::Publisher depth_pub = depth.advertise<scarborough::Depth>("DEPTH", 200);

	while(ros::ok()){
		realDepth.depth = depthSensor.depth();

		depth_pub.publish(realDepth);

		//spin once to let ROS you are alive.
		ros::spinOnce();

	}
}



