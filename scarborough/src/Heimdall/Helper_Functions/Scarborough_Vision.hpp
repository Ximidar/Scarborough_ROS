//
//  Scarborough_Vision.hpp
//  openLOL
//
//  Created by Shubhankar Agarwal on 6/4/16.
//  Copyright © 2016 Shubhankar Agarwal. All rights reserved.
//

#ifndef Scarborough_Vision_hpp
#define Scarborough_Vision_hpp

#include <stdio.h>
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
#include "scarborough/Vision_objects.h"


using namespace std;
using namespace cv;

/// Function header

class Scarborough_Vision{

public:
	void thresh_callback( Mat final_image , double yawO , vector<Point2i> cent_i , vector<double> area1 ,  int thresh, int max_thresh , RNG rng , int g);

	void setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour );

	int filter_image (  Mat detect, Mat src ,  int height , int width , vector<Point2i> cent_i , int red , int green , int blue);

	int filter_image_green (  Mat detect, Mat src ,  int height , int width , vector<Point2i> cent_i , int red , int green , int blue);

	int filterImageHSV (  Mat detect, Mat src ,  int height , int width , vector<Point2i> cent_i , int red , int green , int blue);

	void filterImageHSVRed(  Mat detect, Mat src ,  int height , int width , vector<Point2i> cent_i    );

    void filterImageHSVGreen(  Mat detect, Mat src ,  int height , int width , vector<Point2i> cent_i  );

    void filterImageHSVYellow(  Mat detect, Mat src ,  int height , int width , vector<Point2i> cent_i );

	void direction(vector<Point>  target , double yawO , vector<Point2i> cent_i  , int framecounter , vector<double> area1 , double curr_depth);

	void MyLine( Mat img, Point start, Point end );
	//void drawinglogistics();
	vector<Point>   all_bouy( Mat detect , Mat final_image , double yawI , vector<Point2i> cent_i , vector<double> area1 ,  int thresh, int max_thresh , RNG rng , int g , vector<vector<Point> > contours , int color);
	void drawcontours(Mat final_image  , vector<vector<Point> > contours , int color_bouy , vector<Point> contour_r , vector<Point> contour_g , vector<Point> contour_y );

	void pathmarker( Mat final_image , double yawI , vector<Point2i> cent_i , vector<double> area1 ,  int thresh, int max_thresh , RNG rng , int g);
	scarborough::Vision_objects path_marker;
    scarborough::Vision_objects red_bouy;
	//scarborough::Vision_objects gate;
};



#endif /* Scarborough_Vision_hpp */
