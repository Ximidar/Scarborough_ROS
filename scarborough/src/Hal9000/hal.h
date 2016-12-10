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
#include "../Heimdall/OBJECT_CONSTANTS.h"
#include "scarborough/Desired_Directions.h"
#include "scarborough/YPR.h"
#include "scarborough/Kill_Switch.h"
#include "scarborough/Depth.h"
#include "scarborough/Vision_objects.h"
#include "../HandlerNames/HANDLER_NAMES.h"
#include "scarborough/Hal.h"




using namespace std;



class Hal{
	public:
	//different states
		enum Hal_State {
			DIVE,
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
		void set_rot(double _rotation[3]);
		void set_depth(double _depth);
		void set_vision(scarborough::Vision_objects _vision);
		void maintain_heading();
		Hal_State check_status();

		string state_check; //Alex 2016-07-25: is state check supposed to always be a string of the current state?
							//if that's the case, it would make sense to replace it with a function that returns the state as a string
							//instead of always updating state_check

		bool killed;
		double rotation[3];
		double depth;
		scarborough::Vision_objects gate;
		scarborough::Vision_objects red_bouy;
		scarborough::Vision_objects green_bouy;
		scarborough::Vision_objects yellow_bouy;
		scarborough::Vision_objects flourish_gate;
		scarborough::Vision_objects path_marker;



		double time;
		double timer;



		//desired values

		//bool flags
		bool bouy_state;
		bool gate_state;
		bool path_state;

		Hal_State current_state;

		int bumped;

		//desired message
		scarborough::Desired_Directions desired;


		//object names
		VISION_OBJECTS object_names;
private:

};



#endif /* HAL_H_ */
