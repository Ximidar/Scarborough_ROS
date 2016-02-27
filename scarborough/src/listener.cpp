/*
 * listener.cpp
 *
 *  Created on: Jan 24, 2016
 *      Author: sdcr
 */

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "scarborough/Motor_Speed.h"
#include <string>

using namespace std;

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 * TODO
 * Need to make a new listener.cpp for the motors over the i2c bus to send the motor value
 * to the motors over the i2c bus.
 */
void chatterCallback(const scarborough::Motor_Speed& msg)
{
	for(int i =0 ; i < 6 ; i++){
		ROS_INFO("I heard: [%s]", boost::lexical_cast<std::string>(msg.motor[i]).c_str());
	}

}

int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "listener");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  //ros::NodeHandle n;
  	ros::NodeHandle arduino;

  /**
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.  This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing.  Messages are passed to a callback function, here
   * called chatterCallback.  subscribe() returns a Subscriber object that you
   * must hold on to until you want to unsubscribe.  When all copies of the Subscriber
   * object go out of scope, this callback will automatically be unsubscribed from
   * this topic.
   *
   * The second parameter to the subscribe() function is the size of the message
   * queue.  If messages are arriving faster than they are being processed, this
   * is the number of messages that will be buffered up before beginning to throw
   * away the oldest ones.
   */
  //ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
  ros::Subscriber ard = arduino.subscribe("arduino_chatter", 1000, chatterCallback);

  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
  ros::spin();

  return 0;
}


