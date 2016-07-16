/*
 * hal.cpp
 *
 *  Created on: Feb 25, 2016
 *      Author: sdcr
 */
#include "hal.h"

Handler scarborough_handler1;

Hal::Hal(){

	//initialize
	bouy_state = false;
	gate_state = false;
	path_state = false;
	//setup all variables here.
//	desired_direction = n.advertise<scarborough::Desired_Directions>(handler.HAL, 200);
//	current_direction = n.subscribe<scarborough::YPR>(handler.IMU, 200, getdata);
}

void Hal::init(){
	current_state = Hal::RESET;
	update_state(UPDATE_HDD);
	desired_direction = n.advertise<scarborough::Desired_Directions>(scarborough_handler1.DESIRED, 200);
}

void Hal::update_state(Hal_State state){
	current_state = state;
}
void Hal::update_desired(){


	desired_direction.publish(desired);

}

void Hal::reset(){
	if(killed){
		update_state(Hal::HALT);
	}
	else{
		update_state(Hal::UPDATE_HDD);
		bouy_state = false;
		gate_state = false;
		path_state = false;

		//initialize heading
		for(int i =0 ; i < 3 ; i++){
			desired.rotation[i] = 0;
		}
		desired.throttle = 0;
		desired.depth = 4;

		update_desired();
		init();
	}

}

void Hal::state_loop(Hal_State state){

	switch(state){
	case MAINTAIN_HDD:

		//check flags. IE: Check if any conditions have risen up

		update_state(check_status());

		break;
	case UPDATE_HDD:
		update_desired();
		update_state(Hal::MAINTAIN_HDD);
		break;

	/////////////////////////////////////////PATH MARKER///////////////////////////
	case PATH_DETECT:

		break;


	///////////////////////////////////////////GATE////////////////////////////////
	case GATE_DETECT:

		break;
	case GATE_FLOURISH:

		break;
	case GATE_FINISH:

		break;

	////////////////////////////////////////////BOUY////////////////////////////
	case BOUY_BUMP:

		break;
	case BACKUP:

		break;
	case BOUY_SEARCH:

		break;
	case BOUY_FINISH:

		break;

				//RESET
	case RESET:
		reset();

		break;

	case HALT:
		if(!killed){
			update_state(Hal::RESET);
		}
		break;
	}

}

void Hal::set_killer(bool _killed){
	killed = _killed;
}


Hal::Hal_State Hal::check_status(){

	//TODO Matt Pedler make this check the
	//status of the cameras and Sensors, then return the state, if we even have any you loser

	return RESET;
}





