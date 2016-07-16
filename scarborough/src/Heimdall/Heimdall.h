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
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/photo/photo.hpp"
#include "Helper_Functions/allbouy.hpp"
#include "Helper_Functions/pathmarker.hpp"
#include "Helper_Functions/Scarborough_Vision.hpp"
#include "scarborough/Vision_objects.h"

using namespace std;
using namespace cv;

class Heimdall{

public:
	Heimdall();
	enum gui{
			SHOW_VIDEO,
			HIDE_VIDEO
		};
	void init();
	void hemdall_bouy(gui interface);



	double yawI;
	int thresh;
	int max_thresh;
	RNG rng;

	VideoCapture forward;
	VideoCapture downward;


	/// Global variables
	Mat src, detect_r , detect_g , detect_y ; //, final_image;

	vector<double> area1;


private:

};


#endif /* SRC_HEIMDALL_HEIMDALL_H_ */
