cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})




#############################################################################
#Example talker and listeners
#############################################################################
#rosbuild_add_executable(talker src/talker.cpp)
#rosbuild_add_executable(listener src/listener.cpp)

##############################################################################
#Ardi2c Executable
##############################################################################
#link libraries for ArdI2C(src/arduino_comm.cpp)
FIND_LIBRARY(LOCAL_LIBS libserial.so libserial.a  /usr/local/lib/)

#Add ArdComm executable and add required external libraries for it.

rosbuild_add_executable(ArdI2C src/Arduino_Communications/arduino_i2c.cpp							   
							   src/Arduino_Communications/I2Cdev.cpp)
target_link_libraries(ArdI2C ${LOCAL_LIBS})

##############################################################################
#IMU Executable
##############################################################################

#This executable will be used for getting IMU data from the IMU and publishing it.
rosbuild_add_executable(IMU src/IMU/IMU.cpp
						src/IMU/MPU6050.cpp
						src/IMU/I2Cdev.cpp)

#rosbuild_add_executable(Accel src/IMU/accelerometer/accel_main.cpp
#							  src/IMU/accelerometer/accelerometer.cpp)
#
##############################################################################
#Motor Executable
##############################################################################
rosbuild_add_executable(Motor_Controller src/Motor_Controls/motors_scarborough.cpp
									 src/Motor_Controls/I2Cdev.cpp
									 src/Motor_Controls/Helm.cpp)	
##############################################################################
#Hal Executable
##############################################################################

rosbuild_add_executable(Hal src/Hal9000/Hal_Main.cpp
							 src/Hal9000/hal.cpp
							 src/Hal9000/timer.cpp)

##############################################################################
#Heimdall Executable
##############################################################################
#find openCV							 
#find_package( OpenCV REQUIRED )		 
#
#rosbuild_add_executable(Heimdall src/Heimdall/Heimdall_main.cpp
#								 src/Heimdall/Heimdall.cpp
#								 src/Heimdall/Helper_Functions/Scarborough_Vision.cpp)
#target_link_libraries(Heimdall ${OpenCV_LIBS})	

##############################################################################
#Manual Control
##############################################################################	 
#rosbuild_add_executable(Manual_Control src/Motor_Controls/Manual_Control/Manual_Control.cpp
#									   src/Motor_Controls/I2Cdev.cpp
#						)
