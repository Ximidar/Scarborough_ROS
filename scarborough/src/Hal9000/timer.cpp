/*
 * timer.cpp
 *
 *  Created on: Jul 11, 2016
 *      Author: ximidar
 */

#include "timer.h"

long Timer::return_ms(){
	long ms;

	struct timespec spec;

	clock_gettime(CLOCK_REALTIME, &spec);

	ms = round(spec.tv_nsec / 1.0e6);

	return ms;
}


