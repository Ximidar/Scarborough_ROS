This is the ROS software for the Scarborough Submarine

All source files written by the SDCR team are in the /src and /msg folders

Running this software requires the Scarborough Sub Brain or similar setup(Ubuntu). If you attempt to run this at home be ready
to alter the CMakeLists.txt file to exclude the nodes that your computer cannot support. Be sure not to overwrite the 
CMakeLists.txt file as it is hard to generate and is not intuitive to put back together.

Make sure to have the correct libraries installed so the program does not crash. We are currently using these libraries
 
	LibSerial
	C++ standard libs
	More to come (OpenCV)

/src - Holds all source code for this project.

/src/Arduino_Communications - holds source code for all of the code that deals with communications with the Arduino (i2c, Serial)

/src/IMU - holds all source code for the MPU6050. All this node does is grab the Rotation from the IMU and publish it.

/src/Hal9000 - Holds the source code for the state machine. This is where the Autonomy happens.

/src/Heimdall - Holds source code for the OpenCV code. Currently there is none.

/src/scarborough - holds message code. DO NOT MODIFY. This code is automatically generated 

If you have any questions talk to Matt Pedler.