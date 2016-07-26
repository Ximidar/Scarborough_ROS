/*
 * Heimdall.h
 *
 *  Created on: Jul 16, 2016
 *      Author: ximidar
 */

#ifndef SRC_HEIMDALL_HEIMDALL_H_
#define SRC_HEIMDALL_HEIMDALL_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <sys/time.h>
#include <math.h>
#include "OBJECT_CONSTANTS.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/photo/photo.hpp"
//#include "Helper_Functions/allbouy.hpp"
//#include "Helper_Functions/pathmarker.hpp"
#include "Helper_Functions/Scarborough_Vision.hpp"
#include "scarborough/Vision_objects.h"
#include "scarborough/Depth.h"
#include "../HandlerNames/HANDLER_NAMES.h"
#include "ros/ros.h"
#include "scarborough/Hal.h"

using namespace std;
using namespace cv;

class Heimdall{

public:
	Heimdall();
	enum gui{
			SHOW_VIDEO,
			HIDE_VIDEO
		};
	bool init();
	void heimdall_bouy(gui interface);
	void heimdall_pathmarker(gui interface );
	void get_depth(double _depth);
	void get_state(string _state);
	void test_camera( );

	double depth;
	string state;


	Scarborough_Vision scarborough;
	double yawI;
	int thresh;
	int max_thresh;
	RNG rng;
	vector<Point2i> cent_i;

	VideoCapture forward;
	VideoCapture downward;

	//variables for sharing object data

	scarborough::Vision_objects path_marker;
	scarborough::Vision_objects red_bouy;
	scarborough::Vision_objects gate;

	VISION_OBJECTS objects;


	/// Global variables
	Mat src, detect_r , detect_g , detect_y  , down; //, final_image;

	vector<double> area1;


private:

};


#endif /* SRC_HEIMDALL_HEIMDALL_H_ */
