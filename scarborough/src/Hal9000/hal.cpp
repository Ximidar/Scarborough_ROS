/*
 * hal.cpp
 *
 *  Created on: Feb 25, 2016
 *      Author: sdcr
 */
#include "hal.h"



Hal::Hal(){
	cout << "Made Hal" << endl;
	//initialize
	bouy_state = false;
	gate_state = false;
	path_state = true;
	bumped = 0;
	//setup all variables here.
//	desired_direction = n.advertise<scarborough::Desired_Directions>(handler.HAL, 200);
//	current_direction = n.subscribe<scarborough::YPR>(handler.IMU, 200, getdata);
}

void Hal::init(){
	cout << "Initializing Hal" << endl;
	update_state(RESET);
	
}

void Hal::update_state(Hal_State state){

	current_state = state;


}

void Hal::reset(){
	if(killed){
		current_state = HALT;
		update_state(HALT);
	}
	else{

		cout << "Reset Initiated"<< endl;
		
		bouy_state = false;
		gate_state = true;
		path_state = false;

		//get the yaw offset as the current yaw heading

		desired.rotation[0] = rotation[0];

		//initialize yaw and pitch to be zero since we want it to be level
		for(int i =1 ; i < 3 ; i++){
			desired.rotation[i] = 0;
		}
		desired.throttle = 0;
		desired.depth = 2;
		bumped = 0;

		ros::Duration d(10.0);
		timer = ros::Time::now().toSec() + d.toSec();

		if(rotation[0] == 0){
			update_state(RESET);
		}
		else{
			update_state(MAINTAIN_HDD);
		}
		
	}

}

void Hal::state_loop(Hal_State state){

	switch(state){
	case MAINTAIN_HDD:
		cout << "Maintain HDD" << endl;
		//check flags. IE: Check if any conditions have risen up
		update_state(check_status());


		break;
	case UPDATE_HDD:
		update_state(Hal::MAINTAIN_HDD);
		break;

	/////////////////////////////////////////PATH MARKER///////////////////////////
	case PATH_DETECT:
		cout << "Path Detect" << endl;
		state_check = "PATH";
		if(path_marker.in_sight){
			desired.rotation = path_marker.rotation;
			desired.depth = 4;
			//Alex 2016-07-25: removed desired.throttle = 0 because as (as far as i can tell) there's no code to put it back to a normal value after the rotation
			update_state(UPDATE_HDD);
			//Alex 2016-07-25: removed path_state = false so that more than one path marker can be detected and this one can be followed more closely
			//this way, the sub will align its heading with the path marker while moving over it
			//TODO in the vision code for the path marker, make sure that a partial view of the marker with no clear line doesn't get sent up
		}
		else{

			update_state(UPDATE_HDD);
		}


		break;


	///////////////////////////////////////////GATE////////////////////////////////
	case GATE_DETECT:
			state_check = "GATE";
			cout << "Gate Detection" << endl;
			//keep the initial settings dont change the direction
			desired.depth = 2.0;
			desired.throttle = 1700;
			update_state(UPDATE_HDD);


		break;
	case GATE_FLOURISH:

		break;
	case GATE_FINISH:

		break;

	////////////////////////////////////////////BOUY////////////////////////////
	case BOUY_BUMP:
		cout << "Bouy Bumping Uglies" << endl;
		state_check = "BOUY";

		if(bumped == 0){
			desired.rotation = red_bouy.rotation;
			desired.depth = red_bouy.depth;


		}

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
		else{
			cout << "Halting" << endl;;
		}
		break;

	default: //Alex 2016-07-25: I know that this is impossible. That's exactly why we need to check for it.

		update_state(MAINTAIN_HDD);
		cout << "I CAN'T DO THAT DAVE. DEFAULT HIT" << state << endl;

		break;
	}

}

void Hal::set_killer(bool _killed){
	killed = _killed;
}


Hal::Hal_State Hal::check_status(){

	//TODO Matt Pedler make this check the
	//status of the cameras and Sensors, then return the state,
	//if we even have any you loser
	cout << "Checking status: " ;
	Hal_State change_state;

	if(ros::Time::now().toSec() > timer && gate_state){

		desired.throttle = 1500;

		gate_state = false;
		path_state = true;
		bouy_state = true;
	}

	//Alex 2016-07-25: arranged status checks in order of priority; before, a path marker would take priority over a buoy
	if(killed){ //Alex 2016-07-25: added check for the kill switch; Not checking the switch here may be why the motors turned on unexpectedly.
		change_state = HALT;
	}
	else if(bouy_state && red_bouy.in_sight){
		change_state = BOUY_BUMP;
	}
	else if(path_state && path_marker.in_sight){
		change_state =  PATH_DETECT;
	}
	else if(gate_state){
		change_state =  GATE_DETECT;   
	}
	else if (!gate_state)
	{
		// if we stay in this state too long should we just surface?
		// are we human or are we dancer?
		change_state = MAINTAIN_HDD;
	}
	cout << change_state << endl;

	return change_state;


}

void Hal::maintain_heading(){
	update_state(check_status());

}

void Hal::set_rot(double _rotation[3]){
	for (int i = 0 ; i < 3 ; i++){
		rotation[i] = _rotation[i];
		cout << i << " " << rotation[i] << endl;
	}
}
void Hal::set_depth(double _depth){
	depth = _depth;
}

void Hal::set_vision(scarborough::Vision_objects _vision){




	if(_vision.object == object_names.BOUY){
		if(_vision.color == object_names.RED){
			red_bouy = _vision;
		}
		else if(_vision.color == object_names.GREEN){
			green_bouy = _vision;
		}
		else if(_vision.color == object_names.YELLOW){
			yellow_bouy = _vision;
		}
	}



	if(_vision.object ==  object_names.GATE){
		gate = _vision;
	}


	if(_vision.object ==  object_names.PATH_MARKER){
		path_marker = _vision;
	}


	if(_vision.object ==  object_names.FLOURISH_GATE){
		flourish_gate = _vision;
	}

}

