/*
 * Heimdall_main.cpp
 *
 *  Created on: Jul 16, 2016
 *      Author: ximidar
 */

#include "Heimdall.h"

Heimdall vision;
int main(int argc, char **argv){
	vision.init();
	vision.hemdall_bouy(vision.HIDE_VIDEO);
}


