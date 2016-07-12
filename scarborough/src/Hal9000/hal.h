/*
 * hal.h
 *
 *  Created on: Feb 25, 2016
 *      Author: sdcr
 */

/*
 * Hal9000 was the futuristic machine off of the movie "2001:A Space Oddysey"
 * This Hal is the State machine that will take in all information from the other
 * processes and then decide what the entire machine should do. All debug messages
 * from this program should be "I Can't do that Dave" Hopefully a Dave will work on
 * this code in the future and get really freaked out by it.
 */
#ifndef HAL_H_
#define HAL_H_

#include <iostream>
#include "timer.h"
#include "ros/ros.h"
#include "scarborough/Desired_Directions"
#include "scarborough/YPR.h"
#include "scarborough/Kill_Switch.h"
#include "scarborough/Depth.h"
#include "../HandlerNames/HANDLER_NAMES.h"



using namespace std;



class Hal{
	public:
	//different states
		enum Hal_State {
			MAINTAIN_HDD,
			UPDATE_HDD,

			//PATH MARKER
			PATH_DETECT,


			//GATE
			GATE_DETECT,
			GATE_FLOURISH,
			GATE_FINISH,

			//BOUY
			BOUY_BUMP,
			BACKUP,
			BOUY_SEARCH,
			BOUY_FINISH,

			//RESET
			RESET,
			HALT
		};
		Hal();
		void init();
		void update_state(Hal_State state);
		void update_desired(); // updates desired ypr
		void reset();
		void state_loop(Hal_State state);
		void set_killer(bool _killed);


		Hal_State check_status();

		bool killed;

		Timer time;

		//desired values

		//bool flags
		bool bouy_state;
		bool gate_state;
		bool path_state;

		Hal_State current_state;

		//desired message
		scarborough::Desired_Directions desired;





	private:
		ros::NodeHandle n;
		ros::Publisher desired_direction;




};



#endif /* HAL_H_ */
